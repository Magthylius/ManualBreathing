// Fill out your copyright notice in the Description page of Project Settings.


#include "World/MB_EarthActor.h"

AMB_EarthActor::AMB_EarthActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	GetStaticMeshComponent()->SetCollisionProfileName("NoCollision");

	AtmosphereComponent = CreateDefaultSubobject<UStaticMeshComponent>("AtmosphereComponent");
	AtmosphereComponent->SetupAttachment(RootComponent);
	AtmosphereComponent->SetCollisionProfileName("NoCollision");

	CloudsComponent = CreateDefaultSubobject<UStaticMeshComponent>("CloudsComponent");
	CloudsComponent->SetupAttachment(RootComponent);
	CloudsComponent->SetCollisionProfileName("NoCollision");
}
