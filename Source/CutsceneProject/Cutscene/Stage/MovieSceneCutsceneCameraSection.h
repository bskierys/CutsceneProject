#pragma once


#include "CoreMinimal.h"
#include "MovieSceneSection.h"
#include "Channels/MovieSceneIntegerChannel.h"
#include "MovieSceneCutsceneCameraSection.generated.h"

UCLASS()
class CUTSCENEPROJECT_API UMovieSceneCutsceneCameraSection : public UMovieSceneSection
{
	GENERATED_BODY()

public:
	UMovieSceneCutsceneCameraSection();

	UPROPERTY()
	FMovieSceneIntegerChannel CameraEventChannel;

	virtual TSharedPtr<FStructOnScope> GetKeyStruct(TArrayView<const FKeyHandle> KeyHandles) override;
};