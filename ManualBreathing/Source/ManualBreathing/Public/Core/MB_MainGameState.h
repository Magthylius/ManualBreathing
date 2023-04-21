// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "World/MB_HabitatActor.h"
#include "MB_MainGameState.generated.h"

/**
 * 
 */
UCLASS()
class MANUALBREATHING_API AMB_MainGameState : public AGameStateBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "01 Settings", meta = (AllowPrivateAccess))
	TSubclassOf<AMB_HabitatActor> HabitatActorClass;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "02 Runtime Data", meta = (AllowPrivateAccess))
	TArray<AActor*> PotentialHabitats;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "02 Runtime Data", meta = (AllowPrivateAccess))
	TObjectPtr<AMB_HabitatActor> TrueHabitat;
};
