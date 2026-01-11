#include "MovieSceneCutsceneCameraTrack.h"
#include "MovieSceneCutsceneCameraSection.h"
#include "MovieSceneCutsceneCameraTemplate.h"

bool UMovieSceneCutsceneCameraTrack::SupportsType(
	TSubclassOf<UMovieSceneSection> SectionClass) const
{
	return SectionClass == UMovieSceneCutsceneCameraSection::StaticClass();
}

UMovieSceneSection* UMovieSceneCutsceneCameraTrack::CreateNewSection()
{
	UMovieSceneCutsceneCameraSection* Section =
		NewObject<UMovieSceneCutsceneCameraSection>(this, NAME_None, RF_Transactional);

	Sections.Add(Section);
	return Section;
}

FText UMovieSceneCutsceneCameraTrack::GetDisplayName() const
{
	return FText::FromString("Camera Control");
}

void UMovieSceneCutsceneCameraTrack::AddSection(UMovieSceneSection& Section)
{
	Sections.Add(&Section);
}

void UMovieSceneCutsceneCameraTrack::RemoveSection(UMovieSceneSection& Section)
{
	Sections.Remove(&Section);
}

bool UMovieSceneCutsceneCameraTrack::IsEmpty() const
{
	return Sections.Num() == 0;
}

FMovieSceneEvalTemplatePtr
UMovieSceneCutsceneCameraTrack::CreateTemplateForSection(
	const UMovieSceneSection& InSection) const
{
	return FMovieSceneCutsceneCameraTemplate(
		static_cast<const UMovieSceneCutsceneCameraSection&>(InSection));
}
