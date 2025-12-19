#pragma once
#include "MovieSceneTrackEditor.h"

class FSubtitleTrackEditor : public FMovieSceneTrackEditor
{
public:
	FSubtitleTrackEditor(TSharedRef<ISequencer> InSequencer);

	virtual ~FSubtitleTrackEditor() override
	{
	}

	// FMovieSceneTrackEditor interface
	virtual TSharedRef<ISequencerTrackEditor> CreateTrackEditor(TSharedRef<ISequencer> InSequencer)
	{
		return MakeShared<FSubtitleTrackEditor>(InSequencer);
	}

	virtual void BuildAddTrackMenu(FMenuBuilder& MenuBuilder) override;
	virtual bool SupportsType(TSubclassOf<UMovieSceneTrack> Type) const override;
	virtual TSharedPtr<SWidget> BuildOutlinerEditWidget(
		const FGuid& ObjectBinding,
		UMovieSceneTrack* Track,
		const FBuildEditWidgetParams& Params
	) override;
	virtual void BuildTrackContextMenu(
		FMenuBuilder& MenuBuilder,
		UMovieSceneTrack* Track
	) override;

	void HandleAddSubtitleSection(UMovieSceneTrack* Track);

	// Create custom section interface
	virtual TSharedRef<ISequencerSection> MakeSectionInterface(UMovieSceneSection& SectionObject,
	                                                           UMovieSceneTrack& Track, FGuid ObjectBinding) override;
	static TSharedRef<ISequencerTrackEditor> CreateTrackEditorInstance(TSharedRef<ISequencer> InSequencer);

private:
	void HandleAddSubtitleTrack();
};
