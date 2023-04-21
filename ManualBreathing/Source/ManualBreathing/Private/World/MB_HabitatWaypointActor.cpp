// Fill out your copyright notice in the Description page of Project Settings.


#include "World/MB_HabitatWaypointActor.h"

#include "Core/MB_MainGameState.h"
#include "Kismet/KismetMathLibrary.h"

AMB_HabitatWaypointActor::AMB_HabitatWaypointActor()
{
	PointerStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("PointerStaticMeshComponent");
	PointerStaticMesh->SetupAttachment(RootComponent);
	PrimaryActorTick.bCanEverTick = true;
}

void AMB_HabitatWaypointActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!IsValid(TrueHabitat))
	{
		if (const AMB_MainGameState* GameState = GetWorld()->GetGameState<AMB_MainGameState>())
		{
			AMB_HabitatActor* CurrentHabitat = GameState->GetTrueHabitat();

			if (!IsValid(CurrentHabitat)) return;
			TrueHabitat = CurrentHabitat;
		}
	}

	const FRotator HabitatDirection = UKismetMathLibrary::FindLookAtRotation(PointerStaticMesh->GetComponentLocation(), TrueHabitat->GetActorLocation());
	PointerStaticMesh->SetWorldRotation(HabitatDirection);
}


