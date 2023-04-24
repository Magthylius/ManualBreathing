// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/MB_InteractionPromptWidget.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"

void UMB_InteractionPromptWidget::SetInteractionPhrase(const FString InteractionPhrase) const
{
	FString InteractionPrompt = "Press [";

	const APlayerController* PlayerController = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	const UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
	const TArray<FKey> InputKeys = Subsystem->QueryKeysMappedToAction(InteractInputAction);

	for (int i = 0; i < InputKeys.Num(); i++)
	{
		InteractionPrompt += InputKeys[i].ToString();
		if (i < InputKeys.Num() - 1) InteractionPrompt += "/";
	}

	InteractionPrompt += "] to " + InteractionPhrase;

	InteractionTextBlock->SetText(FText::FromString(InteractionPrompt));
}
