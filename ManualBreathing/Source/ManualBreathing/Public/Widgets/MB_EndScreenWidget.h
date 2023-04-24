// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Styling/SlateColor.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Components/TextBlock.h"
#include "MB_EndScreenWidget.generated.h"

USTRUCT(BlueprintType)
struct FMB_EndScreenOutcome
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	bool bPlayerHasWon = false;
	UPROPERTY(EditAnywhere)
	float TimeTaken;
	UPROPERTY(EditAnywhere)
	float OxygenBreathed;
	UPROPERTY(EditAnywhere)
	int BreathsTaken;
};

DECLARE_MULTICAST_DELEGATE(FRestartGameSignature);
DECLARE_MULTICAST_DELEGATE(FQuitGameSignature);

/**
 * 
 */
UCLASS()
class MANUALBREATHING_API UMB_EndScreenWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	FRestartGameSignature OnRestartGame;
	FQuitGameSignature OnQuitGame;
	
	void SetOutcome(const FMB_EndScreenOutcome Outcome);

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UFUNCTION()
	void OnRestartButton();
	UFUNCTION()
	void OnQuitButton();
	
	UFUNCTION()
	void StartShowTitle() { bShowTitle = true; }
	UFUNCTION()
	void StartShowTimeTaken() { bShowTimeTaken = true; }
	UFUNCTION()
	void StartShowOxygenBreathed() { bShowOxygenBreathed = true; }
	UFUNCTION()
	void StartShowBreathsTaken() { bShowBreathsTaken = true; }
	UFUNCTION()
	void StartShowButtons() { bShowButtons = true; }
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (BindWidget, AllowPrivateAccess))
	TObjectPtr<UTextBlock> TitleTextBlock;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (BindWidget, AllowPrivateAccess))
	TObjectPtr<UTextBlock> TimeTakenTextBlock;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (BindWidget, AllowPrivateAccess))
	TObjectPtr<UTextBlock> OxygenBreathedTextBlock;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (BindWidget, AllowPrivateAccess))
	TObjectPtr<UTextBlock> BreathsTakenTextBlock;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (BindWidget, AllowPrivateAccess))
	TObjectPtr<UCanvasPanel> ButtonCanvasPanel;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (BindWidget, AllowPrivateAccess))
	TObjectPtr<UButton> RestartButton;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (BindWidget, AllowPrivateAccess))
	TObjectPtr<UButton> QuitButton;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", meta= (AllowPrivateAccess))
	float OpacitySpeed = 2.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", meta= (AllowPrivateAccess))
	float ShowDelay = 2.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", meta= (AllowPrivateAccess))
	FString WinningText = "YOU SURVIVED!";
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", meta= (AllowPrivateAccess))
	FString LosingText = "YOU PERISHED...";
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", meta= (AllowPrivateAccess))
	FSlateColor WinningColor = FColor::Green;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", meta= (AllowPrivateAccess))
	FSlateColor LosingColor = FColor::Red;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Runtime Data", meta = (AllowPrivateAccess))
	bool bShowTitle = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Runtime Data", meta = (AllowPrivateAccess))
	bool bShowTimeTaken = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Runtime Data", meta = (AllowPrivateAccess))
	bool bShowOxygenBreathed = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Runtime Data", meta = (AllowPrivateAccess))
	bool bShowBreathsTaken = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Runtime Data", meta = (AllowPrivateAccess))
	bool bShowButtons = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Runtime Data", meta = (AllowPrivateAccess))
	FTimerHandle ShowTitleHandle;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Runtime Data", meta = (AllowPrivateAccess))
	FTimerHandle ShowTimeHandle;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Runtime Data", meta = (AllowPrivateAccess))
	FTimerHandle ShowOxygenBreathedHandle;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Runtime Data", meta = (AllowPrivateAccess))
	FTimerHandle ShowBreathsTakenHandle;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Runtime Data", meta = (AllowPrivateAccess))
	FTimerHandle ShowButtonsHandle;
};
