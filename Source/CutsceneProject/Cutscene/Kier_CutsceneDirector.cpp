// Created by Bartłomiej Kierys


#include "Cutscene/Kier_CutsceneDirector.h"

// Sets default values
AKier_CutsceneDirector::AKier_CutsceneDirector()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AKier_CutsceneDirector::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKier_CutsceneDirector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

