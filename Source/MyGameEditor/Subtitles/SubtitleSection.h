#pragma once

#include "ISequencerSection.h"
#include "MovieSceneSection.h"

class FSubtitleSection : public ISequencerSection
{
public:
	FSubtitleSection(UMovieSceneSection& InSection);

	// ISequencerSection interface
	virtual int32 OnPaintSection( FSequencerSectionPainter& InPainter ) const override;
	virtual FText GetSectionTitle() const override;
	virtual FText GetSectionToolTip() const override;
	virtual UMovieSceneSection* GetSectionObject() override { return &SectionObject; }

private:
	UMovieSceneSection& SectionObject;
};
