// Created by Bartłomiej Kierys

#pragma once

#include "CoreMinimal.h"
#include "LevelSequence.h"
#include "Other/ObjectWithWorld.h"
#include "UObject/NoExportTypes.h"
#include "CutsceneLogic.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable, DefaultToInstanced, EditInlineNew)
class CUTSCENEPROJECT_API UCutsceneLogic : public UObjectWithWorld
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly)
	AGameStateBase* GameState;

	virtual void Init_Implementation(UWorld* World) override;

	/**
	 * Does the Logic has next step.
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, BlueprintPure, Category="Cutscenes")
	bool IsAtFirstStep() const;
	virtual bool IsAtFirstStep_Implementation() const;
	
	/**
	 * Does the Logic has next step.
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, BlueprintPure, Category="Cutscenes")
	bool HasNextStep() const;
	virtual bool HasNextStep_Implementation() const;

	/**
	 * Go to the next stage of Cutscene Logic.
	 * @return Was Advancing to the next step successful?
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Cutscenes")
	bool AdvanceStep();
	virtual bool AdvanceStep_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Cutscenes")
	ULevelSequence* GetCurrentStepSequence();
	virtual ULevelSequence* GetCurrentStepSequence_Implementation();
};
