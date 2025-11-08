// Created by Bartłomiej Kierys

#include "Cutscene/Kier_CutsceneLogic.h"
#include "Kismet/GameplayStatics.h"
#include "Other/WorldLibrary.h"

void UKier_CutsceneLogic::Init_Implementation(UWorld* World)
{
	CachedWorld = TWeakObjectPtr(World);
	if (CachedWorld.IsValid())
	{
		GameState = UGameplayStatics::GetGameState(CachedWorld.Get());
	}
}

bool UKier_CutsceneLogic::IsAtFirstStep_Implementation() const
{
	return true;
}

bool UKier_CutsceneLogic::HasNextStep_Implementation() const
{
	return false;
}

bool UKier_CutsceneLogic::AdvanceStep_Implementation()
{
	return false;
}

ULevelSequence* UKier_CutsceneLogic::GetCurrentStepSequence_Implementation()
{
	return nullptr;
}
