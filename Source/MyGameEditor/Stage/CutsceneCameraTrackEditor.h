#pragma once
#include "MovieSceneTrackEditor.h"

class FCutsceneCameraTrackEditor : public FMovieSceneTrackEditor
{
public:
	static TSharedRef<ISequencerTrackEditor> Create(TSharedRef<ISequencer> Sequencer);

	FCutsceneCameraTrackEditor(TSharedRef<ISequencer> InSequencer);

	// FMovieSceneTrackEditor interface
	virtual TSharedRef<ISequencerTrackEditor> CreateTrackEditor(TSharedRef<ISequencer> InSequencer)
	{
		return MakeShared<FCutsceneCameraTrackEditor>(InSequencer);
	}

	virtual bool SupportsType(TSubclassOf<UMovieSceneTrack> Type) const override;
	virtual void BuildAddTrackMenu(FMenuBuilder& MenuBuilder) override;
	virtual TSharedPtr<SWidget> BuildOutlinerEditWidget(
		const FGuid& ObjectBinding,
		UMovieSceneTrack* Track,
		const FBuildEditWidgetParams& Params
	) override;
	virtual void BuildTrackContextMenu(
		FMenuBuilder& MenuBuilder,
		UMovieSceneTrack* Track
	) override;

	virtual TSharedRef<ISequencerSection> MakeSectionInterface(
		UMovieSceneSection& SectionObject,
		UMovieSceneTrack& Track, FGuid ObjectBinding) override;
	static TSharedRef<ISequencerTrackEditor> CreateTrackEditorInstance(TSharedRef<ISequencer> InSequencer);

private:
	void HandleAddCameraTrack();
};
