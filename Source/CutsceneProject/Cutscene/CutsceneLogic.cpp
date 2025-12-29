// Created by Bartłomiej Kierys

#include "Cutscene/CutsceneLogic.h"
#include "Kismet/GameplayStatics.h"

void UCutsceneLogic::BeginDestroy()
{
	Super::BeginDestroy();
	OnNextSequenceStep.Clear();
	OnLastSequenceStep.Clear();
	OnSkipSequenceStep.Clear();
}

void UCutsceneLogic::Init_Implementation(UWorld* World)
{
	Super::Init_Implementation(World);
	if (CachedWorld.IsValid())
	{
		GameState = UGameplayStatics::GetGameState(CachedWorld.Get());
	}
}

void UCutsceneLogic::AdvanceStep_Implementation()
{
}

void UCutsceneLogic::BroadcastNextSequenceStep(FCutsceneSequencerStep NextStep)
{
	OnNextSequenceStep.Broadcast(NextStep);
}

void UCutsceneLogic::BroadcastLastSequenceStep()
{
	OnLastSequenceStep.Broadcast();
}

void UCutsceneLogic::BroadcastSkipSequenceStep()
{
	OnSkipSequenceStep.Broadcast();
}
