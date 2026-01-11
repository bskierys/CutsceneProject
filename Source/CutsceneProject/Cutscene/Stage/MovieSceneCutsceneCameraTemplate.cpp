#include "MovieSceneCutsceneCameraTemplate.h"
#include "MovieSceneCutsceneCameraSection.h"
#include "Cutscene/CutsceneSubsystem.h"

void FCutsceneCameraExecutionToken::Execute(
	const FMovieSceneContext& Context,
	const FMovieSceneEvaluationOperand& Operand,
	FPersistentEvaluationData& PersistentData,
	IMovieScenePlayer& Player)
{
	UE_LOG(KierCutsceneSystem, Log, TEXT("Cutscene Camera Event Value: %d"), Value);
}

FMovieSceneCutsceneCameraTemplate::FMovieSceneCutsceneCameraTemplate(
	const UMovieSceneCutsceneCameraSection& Section)
	: Channel(Section.CameraEventChannel)
{}

void FMovieSceneCutsceneCameraTemplate::Evaluate(
	const FMovieSceneEvaluationOperand& Operand,
	const FMovieSceneContext& Context,
	const FPersistentEvaluationData& PersistentData,
	FMovieSceneExecutionTokens& ExecutionTokens) const
{
	int32 Value = 0;

	const TRange<FFrameNumber> EvalRange = Context.GetFrameNumberRange();
	for (int32 Index = 0; Index < Channel.GetTimes().Num(); ++Index)
	{
		const FFrameNumber KeyTime = Channel.GetTimes()[Index];
		if (EvalRange.Contains(KeyTime))
		{
			if (Channel.Evaluate(Context.GetTime(), Value))
			{
				ExecutionTokens.Add(FCutsceneCameraExecutionToken(Value));
			}
		}
	}
}
