#pragma once
#include "MovieSceneExecutionToken.h"
#include "Channels/MovieSceneIntegerChannel.h"
#include "Evaluation/MovieSceneEvalTemplate.h"
#include "MovieSceneCutsceneCameraTemplate.generated.h"


class UMovieSceneCutsceneCameraSection;

struct FCutsceneCameraExecutionToken : IMovieSceneExecutionToken
{
	int32 Value;

	explicit FCutsceneCameraExecutionToken(int32 InValue)
		: Value(InValue)
	{}

	virtual void Execute(
		const FMovieSceneContext& Context,
		const FMovieSceneEvaluationOperand& Operand,
		FPersistentEvaluationData& PersistentData,
		IMovieScenePlayer& Player) override;
};

USTRUCT()
struct FMovieSceneCutsceneCameraTemplate : public FMovieSceneEvalTemplate
{
	GENERATED_BODY()
	
	FMovieSceneIntegerChannel Channel;

	FMovieSceneCutsceneCameraTemplate() = default;
	FMovieSceneCutsceneCameraTemplate(const UMovieSceneCutsceneCameraSection& Section);

	virtual UScriptStruct& GetScriptStructImpl() const override
	{
		return *StaticStruct();
	}
	
	virtual void Evaluate(
		const FMovieSceneEvaluationOperand& Operand,
		const FMovieSceneContext& Context,
		const FPersistentEvaluationData& PersistentData,
		FMovieSceneExecutionTokens& ExecutionTokens) const override;
};
