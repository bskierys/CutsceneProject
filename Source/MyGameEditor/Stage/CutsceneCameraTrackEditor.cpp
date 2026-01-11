#include "CutsceneCameraTrackEditor.h"
#include "Cutscene/Stage/MovieSceneCutsceneCameraTrack.h"

TSharedRef<ISequencerTrackEditor> FCutsceneCameraTrackEditor::CreateTrackEditorInstance(
	TSharedRef<ISequencer> InSequencer)
{
	return MakeShareable(new FCutsceneCameraTrackEditor(InSequencer));
}

FCutsceneCameraTrackEditor::FCutsceneCameraTrackEditor(
	TSharedRef<ISequencer> InSequencer)
	: FMovieSceneTrackEditor(InSequencer)
{}

bool FCutsceneCameraTrackEditor::SupportsType(
	TSubclassOf<UMovieSceneTrack> Type) const
{
	return Type == UMovieSceneCutsceneCameraTrack::StaticClass();
}

void FCutsceneCameraTrackEditor::BuildAddTrackMenu(FMenuBuilder& MenuBuilder)
{
	MenuBuilder.AddMenuEntry(
	FText::FromString("Cutscene Camera"),
	FText::FromString("Add cutscene stage/camera control track"),
	FSlateIcon(FAppStyle::GetAppStyleSetName(), "Sequencer.Tracks.Event"),
		FUIAction(
			FExecuteAction::CreateSP(
				this,
				&FCutsceneCameraTrackEditor::HandleAddCameraTrack
			)
		)
	);
}

void FCutsceneCameraTrackEditor::HandleAddCameraTrack()
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

	UMovieSceneCutsceneCameraTrack* Track = MovieScene->AddTrack<UMovieSceneCutsceneCameraTrack>();

	ensure(Track);
	Track->CreateNewSection();

	if (Track)
	{
		Track->Modify();
		LvlSequencer->NotifyMovieSceneDataChanged(
			EMovieSceneDataChangeType::MovieSceneStructureItemAdded
		);
	}
}

TSharedPtr<SWidget> FCutsceneCameraTrackEditor::BuildOutlinerEditWidget(const FGuid& ObjectBinding,
                                                                        UMovieSceneTrack* Track, const FBuildEditWidgetParams& Params)
{
	return FMovieSceneTrackEditor::BuildOutlinerEditWidget(ObjectBinding, Track, Params);
}

void FCutsceneCameraTrackEditor::BuildTrackContextMenu(FMenuBuilder& MenuBuilder, UMovieSceneTrack* Track)
{
	UMovieSceneCutsceneCameraTrack* CameraTrack = Cast<UMovieSceneCutsceneCameraTrack>(Track);

	if (!CameraTrack)
	{
		return;
	}

	MenuBuilder.AddMenuEntry(
		FText::FromString("Add Section"),
		FText::FromString("Adds a new Cutscene Camera section"),
		FSlateIcon(),
		FUIAction(
			FExecuteAction::CreateLambda([this, CameraTrack]()
			{
				TSharedPtr<ISequencer> Sequencer = GetSequencer();
				if (!Sequencer.IsValid())
				{
					return;
				}

				const FScopedTransaction Transaction(
					FText::FromString("Add Cutscene Camera Section"));

				CameraTrack->Modify();
				CameraTrack->CreateNewSection();

				Sequencer->NotifyMovieSceneDataChanged(
					EMovieSceneDataChangeType::MovieSceneStructureItemAdded
				);
			})
		)
	);
}

TSharedRef<ISequencerSection> FCutsceneCameraTrackEditor::MakeSectionInterface(UMovieSceneSection& SectionObject,
	UMovieSceneTrack& Track, FGuid ObjectBinding)
{
	return FMovieSceneTrackEditor::MakeSectionInterface(SectionObject, Track, ObjectBinding);
}


