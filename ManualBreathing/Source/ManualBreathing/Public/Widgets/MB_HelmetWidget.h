// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Creatures/MB_AstronautCharacter.h"
#include "MB_HelmetWidget.generated.h"

/**
 * 
 */
UCLASS()
class MANUALBREATHING_API UMB_HelmetWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (BindWidget, AllowPrivateAccess))
	TObjectPtr<UTextBlock> HeartRateTextBlock;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (BindWidget, AllowPrivateAccess))
	TObjectPtr<UTextBlock> BreathRateTextBlock;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (BindWidget, AllowPrivateAccess))
	TObjectPtr<UTextBlock> LungCapacityTextBlock;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (BindWidget, AllowPrivateAccess))
	TObjectPtr<UTextBlock> OxygenDisplayTextBlock;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Runtime Data", meta = (AllowPrivateAccess))
	TObjectPtr<AMB_AstronautCharacter> AstronautCharacter;
};
