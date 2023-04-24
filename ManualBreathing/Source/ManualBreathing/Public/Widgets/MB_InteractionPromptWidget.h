// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "MB_InteractionPromptWidget.generated.h"

/**
 * 
 */
UCLASS()
class MANUALBREATHING_API UMB_InteractionPromptWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetInteractionPhrase(const FString InteractionPhrase) const;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (BindWidget, AllowPrivateAccess))
	TObjectPtr<UTextBlock> InteractionTextBlock;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", meta = (AllowPrivateAccess))
	TObjectPtr<UInputAction> InteractInputAction;
};
