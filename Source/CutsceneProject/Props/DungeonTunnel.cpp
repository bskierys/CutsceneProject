// Created by Bartłomiej Kierys

#include "DungeonTunnel.h"

#include "Components/InstancedStaticMeshComponent.h"
#include "Other/MeshSizeLibrary.h"

ADungeonTunnel::ADungeonTunnel()
{
	PrimaryActorTick.bCanEverTick = false;

	Floors = CreateDefaultSubobject<UInstancedStaticMeshComponent>("Floors");
	Walls = CreateDefaultSubobject<UInstancedStaticMeshComponent>("Walls");
	Supports = CreateDefaultSubobject<UInstancedStaticMeshComponent>("Supports");

	RootComponent = Floors;
	Walls->SetupAttachment(RootComponent);
	Supports->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ADungeonTunnel::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADungeonTunnel::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	SetupMeshComponents();

	const float TileSize = UMeshSizeLibrary::GetDungeonWallSizeFromMesh(WallMesh, 400.f);
	const float BaseZ = ElevationInSections * TileSize;

	GenerateFloorMeshes(TileSize, BaseZ);
	GenerateWallMeshes(TileSize, BaseZ);
}

void ADungeonTunnel::SetupMeshComponents()
{
	Floors->ClearInstances();
	Walls->ClearInstances();
	Supports->ClearInstances();

	if (FloorMesh) Floors->SetStaticMesh(FloorMesh);
	if (WallMesh) Walls->SetStaticMesh(WallMesh);
	if (SupportMesh) Supports->SetStaticMesh(SupportMesh);
}

void ADungeonTunnel::GenerateFloorMeshes(float TileSize, float BaseZ) const
{
	for (int32 X = 0; X < LengthInSections; ++X)
	{
		for (int32 Y = 0; Y < WidthInSections; ++Y)
		{
			FVector Loc(X * TileSize, Y * TileSize, BaseZ);
			Floors->AddInstance(FTransform(Loc));

			// Supports below (only if Elevation > 0)
			for (int32 E = 0; E < ElevationInSections; ++E)
			{
				FVector SupportLoc(X * TileSize, Y * TileSize, E * TileSize);
				Supports->AddInstance(FTransform(SupportLoc));
			}
		}
	}
}

void ADungeonTunnel::GenerateWallMeshes(float TileSize, float BaseZ)
{
	for (int32 X = 0; X < LengthInSections; ++X)
	{
		for (int32 H = 0; H < HeightInSections; ++H)
		{
			const float Z = BaseZ + (H * TileSize);

			// Left wall
			const bool bSkipLeft = LeftWallGaps.Contains(H)
				&& LeftWallGaps[H].SkipXIndices.Contains(X);

			if (!bSkipLeft)
			{
				FVector LeftLoc(X * TileSize, -TileSize / 2.f, Z);
				FRotator LeftRot = FRotator(0, 0, 0);
				Walls->AddInstance(FTransform(LeftRot, LeftLoc));
			}

			// Right wall
			const bool bSkipRight = RightWallGaps.Contains(H) &&
				RightWallGaps[H].SkipXIndices.Contains(X);

			if (!bSkipRight)
			{
				FVector RightLoc(X * TileSize, WidthInSections * TileSize - TileSize / 2.f, Z);
				FRotator RightRot = FRotator(0, 0, 0);
				Walls->AddInstance(FTransform(RightRot, RightLoc));
			}
		}
	}
}


