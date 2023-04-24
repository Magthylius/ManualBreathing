// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/MB_MainMenuWidget.h"

#include "Shell/Utils/LogUtils.h"

void UMB_MainMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	StartButton->OnClicked.AddUniqueDynamic(this, &UMB_MainMenuWidget::OnStartButton);
	CreditsButton->OnClicked.AddUniqueDynamic(this, &UMB_MainMenuWidget::OnCreditsButton);
	QuitButton->OnClicked.AddUniqueDynamic(this, &UMB_MainMenuWidget::OnQuitButton);
}

void UMB_MainMenuWidget::OnStartButton()
{
	StartGameEvent.Broadcast();
}

void UMB_MainMenuWidget::OnCreditsButton()
{
	//! Get main hud and open credits widget
	//! TODO: add a screen
	FLogUtils::PrintScreen("SPECIAL THANKS TO ElementalCode#5020 @ UnrealSlackers!");
	FLogUtils::PrintScreen("Vanessa Ong");
	FLogUtils::PrintScreen("Jonathan Tang");
	FLogUtils::PrintScreen("CREDITS (Because we didnt have time for a screen):");
}

void UMB_MainMenuWidget::OnQuitButton()
{
	//! Request quit gracefully
	FGenericPlatformMisc::RequestExit(false);
}
