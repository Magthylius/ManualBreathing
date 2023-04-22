// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/MB_MainMenuWidget.h"

void UMB_MainMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	StartButton->OnClicked.AddUniqueDynamic(this, &UMB_MainMenuWidget::OnStartButton);
	CreditsButton->OnClicked.AddUniqueDynamic(this, &UMB_MainMenuWidget::OnCreditsButton);
	QuitButton->OnClicked.AddUniqueDynamic(this, &UMB_MainMenuWidget::OnQuitButton);
}

void UMB_MainMenuWidget::OnStartButton()
{
	//! Get game state and start game
}

void UMB_MainMenuWidget::OnCreditsButton()
{
	//! Get main hud and open credits widget
}

void UMB_MainMenuWidget::OnQuitButton()
{
	FGenericPlatformMisc::RequestExit(false);
}
