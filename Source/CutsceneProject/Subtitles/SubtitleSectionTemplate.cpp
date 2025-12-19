#include "SubtitleSectionTemplate.h"

#include "SubtitleSubsystem.h"

void FSubtitleExecutionToken::Execute(
	const FMovieSceneContext& Context,
	const FMovieSceneEvaluationOperand& Operand,
	FPersistentEvaluationData& PersistentData,
	IMovieScenePlayer& Player
)
{
	const UWorld* World = Player.GetPlaybackContext()
		                ? Player.GetPlaybackContext()->GetWorld()
		                : nullptr;

	if (!World)
	{
		UE_LOG(KierSubtitleSubsystem, Error, TEXT("Sequencer Token Execution Error: Can't get World Instance"));
		return;
	}

	USubtitleSubsystem* SubtitleSubsystem = World->GetSubsystem<USubtitleSubsystem>();
	if (!SubtitleSubsystem)
	{
		UE_LOG(KierSubtitleSubsystem, Error, TEXT("Sequencer Token Execution Error: SubtitleSubsystem not found"));
		return;
	}

	if (bShow)
	{
		SubtitleSubsystem->ShowSubtitle(Speaker, Text, ColorId);
	}
	else
	{
		SubtitleSubsystem->HideSubtitle();
	}
}

FMovieSceneSubtitleSectionTemplate::FMovieSceneSubtitleSectionTemplate(const UMovieSceneSubtitleSection& InSection)
{
	Speaker = InSection.Speaker;
	SubtitleText = InSection.SubtitleText;
	SubtitleColorId = InSection.SubtitleColorId;
}

void FMovieSceneSubtitleSectionTemplate::Evaluate(
	const FMovieSceneEvaluationOperand& Operand,
	const FMovieSceneContext& Context,
	const FPersistentEvaluationData& PersistentData,
	FMovieSceneExecutionTokens& ExecutionTokens
) const
{
	// PersistentData is passed as const; we need a mutable view to store state.
	FPersistentEvaluationData& MutableData = const_cast<FPersistentEvaluationData&>(PersistentData);

	// Use a shared persistent key; allocate once per template to stay stable.
	static const FMovieSceneSharedDataId SharedDataId = FMovieSceneSharedDataId::Allocate();
	const FSharedPersistentDataKey Key(SharedDataId, Operand);
	FSubtitleSectionPersistentData& State = MutableData.GetOrAdd<FSubtitleSectionPersistentData>(Key);

	const bool bIsActiveNow = Context.GetStatus() == EMovieScenePlayerStatus::Playing
					   || Context.GetStatus() == EMovieScenePlayerStatus::Scrubbing;

	const auto CurrentTime = Context.GetTime();
	const TRange<FFrameNumber> PlaybackRange = Context.GetFrameNumberRange();
	const FFrameNumber ExclusiveEndFrame = UE::MovieScene::DiscreteExclusiveUpper(PlaybackRange.GetUpperBound());

	if (!bIsActiveNow)
	{
		UE_LOG(KierSubtitleSubsystem, Warning, TEXT("Section Template: Invalid state. Hiding subtitles"));
		FSubtitleExecutionToken Token;
		Token.bShow = false;

		ExecutionTokens.Add(MoveTemp(Token));

		State.bWasActive = false;
		return;
	}
	
	// Section ENTER
	if (!State.bWasActive && bIsActiveNow)
	{
		UE_LOG(
			KierSubtitleSubsystem, Log,
			TEXT("Section Template: Subtitle start frame: %s"),
			*LexToString(CurrentTime)
		);
		FSubtitleExecutionToken Token;
		Token.Speaker = Speaker;
		Token.Text = SubtitleText;
		Token.ColorId = SubtitleColorId;
		Token.bShow = true;

		ExecutionTokens.Add(MoveTemp(Token));

		State.bWasActive = true;
	}

	// Section EXIT
	if (State.bWasActive && CurrentTime.FrameNumber == ExclusiveEndFrame)
	{
		UE_LOG(
			KierSubtitleSubsystem, Log,
			TEXT("Section Template: Subtitle end frame: %s"),
			*LexToString(CurrentTime)
		);
		FSubtitleExecutionToken Token;
		Token.bShow = false;

		ExecutionTokens.Add(MoveTemp(Token));

		State.bWasActive = false;
	}
}
