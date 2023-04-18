// Fill out your copyright notice in the Description page of Project Settings.


#include "World/MB_EarthActor.h"

AMB_EarthActor::AMB_EarthActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	AtmosphereComponent = CreateDefaultSubobject<UStaticMeshComponent>("AtmosphereComponent");
	AtmosphereComponent->SetupAttachment(RootComponent);
	
	CloudsComponent = CreateDefaultSubobject<UStaticMeshComponent>("CloudsComponent");
	CloudsComponent->SetupAttachment(RootComponent);
}
