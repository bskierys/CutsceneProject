// Created by Bartłomiej Kierys

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MeshSizeLibrary.generated.h"

/**
 * 
 */
UCLASS()
class CUTSCENEPROJECT_API UMeshSizeLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	 * Calculate the tile size from a static mesh's bounds
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Meshes")
	static float GetDungeonWallSizeFromMesh(const UStaticMesh* Mesh, const float DefaultSize = 400.f);
};
