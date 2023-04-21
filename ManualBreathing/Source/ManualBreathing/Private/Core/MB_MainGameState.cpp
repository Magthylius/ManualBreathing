// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/MB_MainGameState.h"

#include "Kismet/GameplayStatics.h"

void AMB_MainGameState::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), HabitatActorClass, PotentialHabitats);
	
	if (PotentialHabitats.Num() > 0)
	{
		const int RandomIndex = FMath::RandRange(0, PotentialHabitats.Num() -1 );
		TrueHabitat = Cast<AMB_HabitatActor>(PotentialHabitats[RandomIndex]);
		TrueHabitat->ActivateHabitat();
		return;
	}

	UE_LOG(LogTemp, Error, TEXT("AMB_MainGameState: No habitats found!"));
}
