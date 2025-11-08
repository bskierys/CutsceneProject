// Created by Bartłomiej Kierys

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "WorldLibrary.generated.h"

UCLASS()
class CUTSCENEPROJECT_API UWorldLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	/**
	 * @return Gets current UWorld needed for getting pawn and other statistics. Does all the needed null chacks to avoid
	 * crashing the game.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static UWorld* GetWorldSafe();
};
