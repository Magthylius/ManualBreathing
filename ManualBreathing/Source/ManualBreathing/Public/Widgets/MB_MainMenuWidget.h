// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "MB_MainMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class MANUALBREATHING_API UMB_MainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (BindWidget, AllowPrivateAccess))
	TObjectPtr<UButton> StartButton;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (BindWidget, AllowPrivateAccess))
	TObjectPtr<UButton> CreditsButton;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (BindWidget, AllowPrivateAccess))
	TObjectPtr<UButton> QuitButton;

protected:
	virtual void NativeOnInitialized() override;

private:
	UFUNCTION()
	void OnStartButton();
	UFUNCTION()
	void OnCreditsButton();
	UFUNCTION()
	void OnQuitButton();
};
