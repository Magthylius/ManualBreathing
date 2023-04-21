// Fill out your copyright notice in the Description page of Project Settings.


#include "World/MB_HabitatActor.h"

AMB_HabitatActor::AMB_HabitatActor()
{
	SetActorHiddenInGame(true);
}

void AMB_HabitatActor::ActivateHabitat()
{
	SetActorHiddenInGame(false);
}
