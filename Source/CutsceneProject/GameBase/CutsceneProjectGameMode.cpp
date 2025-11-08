// Copyright Epic Games, Inc. All Rights Reserved.

#include "CutsceneProjectGameMode.h"

#include "GameBase/CutsceneProjectGameState.h"
#include "UObject/ConstructorHelpers.h"

ACutsceneProjectGameMode::ACutsceneProjectGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/Characters/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	GameStateClass = ACutsceneProjectGameState::StaticClass();
}
