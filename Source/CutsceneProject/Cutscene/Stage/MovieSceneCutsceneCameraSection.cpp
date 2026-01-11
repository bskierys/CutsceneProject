#include "MovieSceneCutsceneCameraSection.h"
#include "Channels/MovieSceneChannelProxy.h"

UMovieSceneCutsceneCameraSection::UMovieSceneCutsceneCameraSection()
{
	SetRange(TRange<FFrameNumber>::All());

	EvalOptions.EnableAndSetCompletionMode(EMovieSceneCompletionMode::KeepState);
	bSupportsInfiniteRange = true;

#if WITH_EDITOR

	ChannelProxy = MakeShared<FMovieSceneChannelProxy>(
		CameraEventChannel,
		FMovieSceneChannelMetaData(
			TEXT("CameraEvent"),
			FText::FromString("Camera Event"),
			FText::FromString("Integer camera event"),
			true),
		TMovieSceneExternalValue<int32>()
	);

#else

	ChannelProxy = MakeShared<FMovieSceneChannelProxy>(CameraEventChannel);

#endif
}

TSharedPtr<FStructOnScope> UMovieSceneCutsceneCameraSection::GetKeyStruct(TArrayView<const FKeyHandle> KeyHandles)
{
	return MakeShared<FStructOnScope>(FMovieSceneIntegerChannel::StaticStruct());
}
