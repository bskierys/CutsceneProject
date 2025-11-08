// Created by Bartłomiej Kierys

#pragma once

#include "CoreMinimal.h"
#include "CutsceneTrigger.h"
#include "GameFramework/Actor.h"
#include "Kier_CutsceneDirector.generated.h"

class UKier_CutsceneLogic;

UCLASS()
class CUTSCENEPROJECT_API AKier_CutsceneDirector : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKier_CutsceneDirector();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Instanced, Category="Cutscenes")
	UCutsceneTrigger* CutsceneTrigger;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Instanced, Category="Cutscenes")
	UKier_CutsceneLogic* CutsceneLogic;

};
