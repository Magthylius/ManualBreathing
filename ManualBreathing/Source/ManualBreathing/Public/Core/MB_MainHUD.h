// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Widgets/MB_HelmetWidget.h"
#include "Widgets/MB_InteractionPromptWidget.h"
#include "Widgets/MB_MainMenuWidget.h"
#include "MB_MainHUD.generated.h"

/**
 * 
 */
UCLASS()
class MANUALBREATHING_API AMB_MainHUD : public AHUD
{
	GENERATED_BODY()

public:
	UMB_HelmetWidget* SetHelmetWidget(const bool bShowWidget);
	UMB_MainMenuWidget* SetMainMenuWidget(const bool bShowWidget);
	UMB_InteractionPromptWidget* SetInteractionPrompt(const bool bShowWidget);
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "01 Settings", meta = (AllowPrivateAccess))
	TSubclassOf<UMB_HelmetWidget> HelmetWidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "01 Settings", meta = (AllowPrivateAccess))
	TSubclassOf<UMB_MainMenuWidget> MainMenuWidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "01 Settings", meta = (AllowPrivateAccess))
	TSubclassOf<UMB_InteractionPromptWidget> InteractionPromptWidgetClass;
	
	UPROPERTY()
	TObjectPtr<UMB_HelmetWidget> HelmetWidget;
	UPROPERTY()
	TObjectPtr<UMB_MainMenuWidget> MainMenuWidget;
	UPROPERTY()
	TObjectPtr<UMB_InteractionPromptWidget> InteractionPromptWidget;

	UUserWidget* SetWidgetActive(UUserWidget* WidgetInstance, TSubclassOf<UUserWidget> WidgetClass, const bool bShowWidget) const;
};
