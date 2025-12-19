#pragma once

#include "CoreMinimal.h"
#include "Compilation/IMovieSceneTrackTemplateProducer.h"
#include "MovieSceneExecutionToken.h"
#include "MovieSceneSubtitleSection.h"
#include "Evaluation/MovieSceneEvalTemplate.h"
#include "Evaluation/MovieSceneEvaluationField.h"
#include "Evaluation/PersistentEvaluationData.h"
#include "SubtitleSectionTemplate.generated.h"

struct FSubtitleExecutionToken : IMovieSceneExecutionToken
{
	FText Speaker;
	FText Text;
	FName ColorId;
	bool bShow = false;

	virtual void Execute(
		const FMovieSceneContext& Context,
		const FMovieSceneEvaluationOperand& Operand,
		FPersistentEvaluationData& PersistentData,
		IMovieScenePlayer& Player
	) override;
};

struct FSubtitleSectionPersistentData : IPersistentEvaluationData
{
	bool bWasActive = false;
};

USTRUCT()
struct FMovieSceneSubtitleSectionTemplate : public FMovieSceneEvalTemplate
{
	GENERATED_BODY()

	FMovieSceneSubtitleSectionTemplate() = default;
	FMovieSceneSubtitleSectionTemplate(const UMovieSceneSubtitleSection& InSection);

	UPROPERTY()
	FText Speaker;
	
	UPROPERTY()
	FText SubtitleText;

	UPROPERTY()
	FName SubtitleColorId;

	virtual UScriptStruct& GetScriptStructImpl() const override
	{
		return *StaticStruct();
	}

	virtual void Evaluate(
		const FMovieSceneEvaluationOperand& Operand,
		const FMovieSceneContext& Context,
		const FPersistentEvaluationData& PersistentData,
		FMovieSceneExecutionTokens& ExecutionTokens
	) const override;
};
