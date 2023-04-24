// Fill out your copyright notice in the Description page of Project Settings.


#include "World/MB_TitleWidgetActor.h"

AMB_TitleWidgetActor::AMB_TitleWidgetActor()
{
	SceneRoot = CreateDefaultSubobject<USceneComponent>("SceneRoot");
	RootComponent = SceneRoot;
	
	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>("WidgetComponent");
	WidgetComponent->SetupAttachment(RootComponent);
	
	PrimaryActorTick.bCanEverTick = false;
}

void AMB_TitleWidgetActor::SetWidgetHidden(const bool bWidgetHidden) const
{
	WidgetComponent->SetHiddenInGame(bWidgetHidden);
}
