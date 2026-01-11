#pragma once
#include "MovieSceneTrack.h"
#include "Compilation/IMovieSceneTrackTemplateProducer.h"
#include "Evaluation/MovieSceneEvalTemplate.h"
#include "MovieSceneCutsceneCameraTrack.generated.h"

UCLASS()
class CUTSCENEPROJECT_API UMovieSceneCutsceneCameraTrack : public UMovieSceneTrack, public IMovieSceneTrackTemplateProducer
{
	GENERATED_BODY()

public:
	// UMovieSceneTrack interface
	virtual bool SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const override;
	virtual const TArray<UMovieSceneSection*>& GetAllSections() const override { return Sections; }
	virtual UMovieSceneSection* CreateNewSection() override;
	virtual FText GetDisplayName() const override;
	virtual void AddSection(UMovieSceneSection& Section) override;
	virtual void RemoveSection(UMovieSceneSection& Section) override;
	virtual bool IsEmpty() const override;
	
	// IMovieSceneTrackTemplateProducer
	virtual FMovieSceneEvalTemplatePtr CreateTemplateForSection(
		const UMovieSceneSection& InSection) const override;

private:
	UPROPERTY()
	TArray<TObjectPtr<UMovieSceneSection>> Sections;
};