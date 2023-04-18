// Fill out your copyright notice in the Description page of Project Settings.


#include "World/MB_FlyingAsteroid.h"

AMB_FlyingAsteroid::AMB_FlyingAsteroid()
{
	RootComponent->SetMobility(EComponentMobility::Movable);
	GetStaticMeshComponent()->SetSimulatePhysics(true);
	PrimaryActorTick.bCanEverTick = true;
}

void AMB_FlyingAsteroid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsValid(CrashTarget))
	{
		const FVector Direction = CrashTarget->GetActorLocation() - GetStaticMeshComponent()->GetComponentLocation();
		GetStaticMeshComponent()->AddForce(Direction, FName(), true);
	}
}
