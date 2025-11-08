// Created by Bartłomiej Kierys

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "Kier_DeveloperSettings.generated.h"

class USubsystemConfig;
/**
 * Configuration for subsystems in the project.
 */
UCLASS(config = Game, defaultconfig, meta = (DisplayName = "Custom Config"))
class CUTSCENEPROJECT_API UKier_DeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	virtual FName GetCategoryName() const override { return TEXT("Custom Project Config"); }

	UPROPERTY(EditAnywhere, config, Category="Subsystem|Config")
	TArray<TSoftObjectPtr<USubsystemConfig>> SubsystemConfig;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Subsystem|Config")
	USubsystemConfig* GetSubsystemConfigByClass(TSubclassOf<USubsystemConfig> ParamClass) const;
};
