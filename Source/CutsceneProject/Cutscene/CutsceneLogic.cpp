// Created by Bartłomiej Kierys

#include "Cutscene/CutsceneLogic.h"
#include "Kismet/GameplayStatics.h"

void UCutsceneLogic::Init_Implementation(UWorld* World)
{
	Super::Init_Implementation(World);
	if (CachedWorld.IsValid())
	{
		GameState = UGameplayStatics::GetGameState(CachedWorld.Get());
	}
}

bool UCutsceneLogic::IsAtFirstStep_Implementation() const
{
	return true;
}

bool UCutsceneLogic::HasNextStep_Implementation() const
{
	return false;
}

bool UCutsceneLogic::AdvanceStep_Implementation()
{
	return false;
}

ULevelSequence* UCutsceneLogic::GetCurrentStepSequence_Implementation()
{
	return nullptr;
}
