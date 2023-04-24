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

	return Cast<UMB_HelmetWidget>(SetWidgetActive(HelmetWidget, HelmetWidgetClass, bShowWidget));
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
	//return Cast<UMB_MainMenuWidget>(SetWidgetActive(HelmetWidget, HelmetWidgetClass, bShowWidget));
}

UMB_InteractionPromptWidget* AMB_MainHUD::SetInteractionPromptWidget(const bool bShowWidget)
{
	if (!IsValid(InteractionPromptWidget))
	{
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		InteractionPromptWidget = Cast<UMB_InteractionPromptWidget>(CreateWidget(PlayerController, InteractionPromptWidgetClass, FName("Interaction Prompt Widget")));
	}

	if (bShowWidget) InteractionPromptWidget->AddToViewport();
	else InteractionPromptWidget->RemoveFromParent();

	return InteractionPromptWidget;
	//return Cast<UMB_InteractionPromptWidget>(SetWidgetActive(InteractionPromptWidget, InteractionPromptWidgetClass, bShowWidget));
}

UMB_EndScreenWidget* AMB_MainHUD::SetEndScreenWidget(const bool bShowWidget)
{
	if (!IsValid(EndScreenWidget))
	{
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		EndScreenWidget = Cast<UMB_EndScreenWidget>(CreateWidget(PlayerController, EndScreenWidgetClass, FName("End Screen Widget")));
	}

	if (bShowWidget) EndScreenWidget->AddToViewport();
	else EndScreenWidget->RemoveFromParent();

	return EndScreenWidget;
}

//! TODO: fix this
UUserWidget* AMB_MainHUD::SetWidgetActive(UUserWidget* WidgetInstance, TSubclassOf<UUserWidget> WidgetClass, const bool bShowWidget) const
{
	if (!IsValid(WidgetInstance))
	{
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		WidgetInstance = CreateWidget(PlayerController, WidgetClass, FName(WidgetClass->GetName()));
	}

	if (bShowWidget) WidgetInstance->AddToViewport();
	else WidgetInstance->RemoveFromParent();

	return WidgetInstance;
}
