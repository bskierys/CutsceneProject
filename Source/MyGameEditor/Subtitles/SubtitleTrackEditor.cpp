#include "SubtitleTrackEditor.h"
#include "SubtitleSection.h"
#include "Subtitles/MovieSceneSubtitleTrack.h"

FSubtitleTrackEditor::FSubtitleTrackEditor(TSharedRef<ISequencer> InSequencer): FMovieSceneTrackEditor(InSequencer)
{
}

void FSubtitleTrackEditor::BuildAddTrackMenu(FMenuBuilder& MenuBuilder)
{
	MenuBuilder.AddMenuEntry(
		FText::FromString("Subtitles"),
		FText::FromString("Add a subtitle track"),
		FSlateIcon(),
		FUIAction(
			FExecuteAction::CreateSP(
				this,
				&FSubtitleTrackEditor::HandleAddSubtitleTrack
			)
		)
	);
}

bool FSubtitleTrackEditor::SupportsType(TSubclassOf<UMovieSceneTrack> Type) const
{
	return Type == UMovieSceneSubtitleTrack::StaticClass();
}

TSharedPtr<SWidget> FSubtitleTrackEditor::BuildOutlinerEditWidget(
	const FGuid& ObjectBinding,
	UMovieSceneTrack* Track,
	const FBuildEditWidgetParams& Params
)
{
	// Optional: return a widget for the track header in the outliner (e.g. an icon)
	return SNullWidget::NullWidget;
}

void FSubtitleTrackEditor::BuildTrackContextMenu(FMenuBuilder& MenuBuilder, UMovieSceneTrack* Track)
{
	if (!Track || !Track->IsA<UMovieSceneSubtitleTrack>())
	{
		return;
	}

	MenuBuilder.AddMenuEntry(
		FText::FromString("Add Subtitle"),
		FText::FromString("Add a subtitle section"),
		FSlateIcon(),
		FUIAction(
			FExecuteAction::CreateSP(
				this,
				&FSubtitleTrackEditor::HandleAddSubtitleSection,
				Track
			)
		)
	);
}

void FSubtitleTrackEditor::HandleAddSubtitleSection(UMovieSceneTrack* Track)
{
	TSharedPtr<ISequencer> LvlSequencer = GetSequencer();
	if (!LvlSequencer.IsValid())
	{
		return;
	}

	UMovieScene* MovieScene =
		LvlSequencer->GetFocusedMovieSceneSequence()->GetMovieScene();
	if (!MovieScene)
	{
		return;
	}

	const FScopedTransaction Transaction(
		FText::FromString("Add Subtitle Section")
	);

	Track->Modify();

	UMovieSceneSection* NewSection = Track->CreateNewSection();
	if (!NewSection)
	{
		return;
	}

	NewSection->SetIsActive(true);
	NewSection->SetRowIndex(0);

	// Place section at current time
	const FFrameNumber StartFrame =
		LvlSequencer->GetLocalTime().Time.FrameNumber;

	const FFrameNumber Duration =
		MovieScene->GetTickResolution().AsFrameNumber(2.0f); // 2 seconds default

	NewSection->SetRange(TRange<FFrameNumber>(
		StartFrame,
		StartFrame + Duration
	));

	Track->AddSection(*NewSection);

	LvlSequencer->NotifyMovieSceneDataChanged(
		EMovieSceneDataChangeType::MovieSceneStructureItemAdded
	);
}

TSharedRef<ISequencerSection> FSubtitleTrackEditor::MakeSectionInterface(
	UMovieSceneSection& SectionObject,
	UMovieSceneTrack& Track, FGuid ObjectBinding
)
{
	return MakeShared<FSubtitleSection>(SectionObject);
}

TSharedRef<ISequencerTrackEditor> FSubtitleTrackEditor::CreateTrackEditorInstance(TSharedRef<ISequencer> InSequencer)
{
	return MakeShared<FSubtitleTrackEditor>(InSequencer);
}

void FSubtitleTrackEditor::HandleAddSubtitleTrack()
{
	TSharedPtr<ISequencer> LvlSequencer = GetSequencer();
	if (!LvlSequencer.IsValid())
	{
		return;
	}
	
	UMovieScene* MovieScene = LvlSequencer->GetFocusedMovieSceneSequence()->GetMovieScene();

	if (!MovieScene)
	{
		return;
	}

	const FScopedTransaction Transaction(
		FText::FromString("Add Subtitle Track")
	);

	MovieScene->Modify();

	UMovieSceneSubtitleTrack* Track = MovieScene->AddTrack<UMovieSceneSubtitleTrack>();

	if (Track)
	{
		Track->Modify();
		LvlSequencer->NotifyMovieSceneDataChanged(
			EMovieSceneDataChangeType::MovieSceneStructureItemAdded
		);
	}
}
