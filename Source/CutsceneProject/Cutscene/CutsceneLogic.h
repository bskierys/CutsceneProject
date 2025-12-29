// Created by Bartłomiej Kierys

#pragma once

#include "CoreMinimal.h"
#include "LevelSequence.h"
#include "Other/ObjectWithWorld.h"
#include "UObject/NoExportTypes.h"
#include "CutsceneLogic.generated.h"

USTRUCT(BlueprintType)
struct FCutsceneSequencerStep
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ULevelSequence* Sequence;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(
	FOnNextSequenceStep,
	FCutsceneSequencerStep,
	CurrentStep
);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(
	FOnLastSequenceStep
);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(
	FOnSkipSequenceStep
);

UCLASS(Abstract, Blueprintable, DefaultToInstanced, EditInlineNew)
class CUTSCENEPROJECT_API UCutsceneLogic : public UObjectWithWorld
{
	GENERATED_BODY()

public:
	virtual void BeginDestroy() override;
	
	UPROPERTY(BlueprintReadOnly)
	AGameStateBase* GameState;

	virtual void Init_Implementation(UWorld* World) override;
	
	/**
	 * Go to the next stage of Cutscene Logic.
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Cutscenes")
	void AdvanceStep();
	virtual void AdvanceStep_Implementation();

	UPROPERTY(BlueprintAssignable, Category="Cutscenes")
	FOnNextSequenceStep OnNextSequenceStep;
	
	UFUNCTION(BlueprintCallable, Category="Cutscenes")
	void BroadcastNextSequenceStep(FCutsceneSequencerStep NextStep);
	
	UPROPERTY(BlueprintAssignable, Category="Cutscenes")
	FOnLastSequenceStep OnLastSequenceStep;

	UFUNCTION(BlueprintCallable, Category="Cutscenes")
	void BroadcastLastSequenceStep();

	UPROPERTY(BlueprintAssignable, Category="Cutscenes")
	FOnSkipSequenceStep OnSkipSequenceStep;

	UFUNCTION(BlueprintCallable, Category="Cutscenes")
	void BroadcastSkipSequenceStep();
};
