// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/MB_MainHUD.h"
#include "Blueprint/UserWidget.h"

void AMB_MainHUD::BeginPlay()
{
	Super::BeginPlay();
	
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	UUserWidget* HelmetHUDWidget = CreateWidget(PlayerController, HelmetHUD, FName("Helmet HUD"));
	HelmetHUDWidget->AddToViewport();
}
