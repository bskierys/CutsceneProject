// Created by Bartłomiej Kierys

#pragma once

#include "CoreMinimal.h"
#include "LevelSequence.h"
#include "UObject/NoExportTypes.h"
#include "Kier_CutsceneLogic.generated.h"

class ACutsceneProjectGameMode;
/**
 * 
 */
UCLASS(Abstract, Blueprintable, DefaultToInstanced, EditInlineNew)
class CUTSCENEPROJECT_API UKier_CutsceneLogic : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	ACutsceneProjectGameMode* GameMode;

	UPROPERTY(BlueprintReadOnly)
	AGameStateBase* GameState;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Cutscenes")
	void Init();
	virtual void Init_Implementation();

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
