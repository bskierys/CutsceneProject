// Created by Bartłomiej Kierys

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DungeonTunnel.generated.h"

USTRUCT(BlueprintType)
struct FWallGapRow
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSet<int32> SkipXIndices;
};

UCLASS(Blueprintable)
class CUTSCENEPROJECT_API ADungeonTunnel : public AActor
{
	GENERATED_BODY()
	
public:
	ADungeonTunnel();

protected:
	virtual void BeginPlay() override;

	virtual void OnConstruction(const FTransform& Transform) override;

	virtual void SetupMeshComponents();

	void GenerateFloorMeshes(float TileSize, float BaseZ) const;

	void GenerateWallMeshes(float TileSize, float BaseZ);

public:	
	UPROPERTY(EditAnywhere, Category="Dungeon")
	int32 HeightInSections = 2;

	UPROPERTY(EditAnywhere, Category="Dungeon")
	int32 LengthInSections = 5;

	UPROPERTY(EditAnywhere, Category="Dungeon")
	int32 WidthInSections = 2;

	UPROPERTY(EditAnywhere, Category="Dungeon")
	int32 ElevationInSections = 1;

	UPROPERTY(EditAnywhere, Category="Tunnel")
	TMap<int32, FWallGapRow> LeftWallGaps;

	UPROPERTY(EditAnywhere, Category="Tunnel")
	TMap<int32, FWallGapRow> RightWallGaps;

	UPROPERTY(EditAnywhere, Category="Meshes")
	UStaticMesh* WallMesh = nullptr;

	UPROPERTY(EditAnywhere, Category="Meshes")
	UStaticMesh* FloorMesh = nullptr;

	UPROPERTY(EditAnywhere, Category="Meshes")
	UStaticMesh* SupportMesh = nullptr;

protected:
	UPROPERTY()
	UInstancedStaticMeshComponent* Walls = nullptr;

	UPROPERTY()
	UInstancedStaticMeshComponent* Floors = nullptr;

	UPROPERTY()
	UInstancedStaticMeshComponent* Supports = nullptr;
};
