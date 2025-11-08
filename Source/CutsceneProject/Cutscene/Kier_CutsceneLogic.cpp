// Created by Bartłomiej Kierys

#include "Cutscene/Kier_CutsceneLogic.h"
#include "CutsceneProjectGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Other/WorldLibrary.h"

void UKier_CutsceneLogic::Init_Implementation()
{
	const UWorld* World = UWorldLibrary::GetWorldSafe();
	if (IsValid(World))
	{
		GameMode = Cast<ACutsceneProjectGameMode>(UGameplayStatics::GetGameMode(World));
		GameState = UGameplayStatics::GetGameState(World);
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
