// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/MB_MainHUD.h"
#include "Blueprint/UserWidget.h"

UMB_HelmetWidget* AMB_MainHUD::SetHelmetWidget(const bool bShowWidget)
{
	if (!IsValid(HelmetWidget))
	{
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		HelmetWidget = Cast<UMB_HelmetWidget>(CreateWidget(PlayerController, HelmetWidgetClass, FName("Helmet Widget")));
	}

	if (bShowWidget) HelmetWidget->AddToViewport();
	else HelmetWidget->RemoveFromParent();
	
	return HelmetWidget;
}

UMB_MainMenuWidget* AMB_MainHUD::SetMainMenuWidget(const bool bShowWidget)
{
	if (!IsValid(MainMenuWidget))
	{
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		MainMenuWidget = Cast<UMB_MainMenuWidget>(CreateWidget(PlayerController, MainMenuWidgetClass, FName("Main Menu Widget")));
	}

	if (bShowWidget) MainMenuWidget->AddToViewport();
	else MainMenuWidget->RemoveFromParent();

	return MainMenuWidget;
}