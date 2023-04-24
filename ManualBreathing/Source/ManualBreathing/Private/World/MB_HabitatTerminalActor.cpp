// Fill out your copyright notice in the Description page of Project Settings.


#include "World/MB_HabitatTerminalActor.h"

#include "Core/MB_MainGameState.h"
#include "Core/MB_MainHUD.h"
#include "Kismet/GameplayStatics.h"

AMB_HabitatTerminalActor::AMB_HabitatTerminalActor()
{
	GetStaticMeshComponent()->SetGenerateOverlapEvents(true);
}

void AMB_HabitatTerminalActor::BeginInteraction()
{
	AMB_MainGameState* GameState = GetWorld()->GetGameState<AMB_MainGameState>();
	GameState->EndGame(true);
}

void AMB_HabitatTerminalActor::OnEnterInteractionRange(UMB_InteractionComponent* InteractionComponent)
{
	const APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	
	if (!IsValid(PlayerController)) return;
	AMB_MainHUD* MainHUD = PlayerController->GetHUD<AMB_MainHUD>();
	
	if (!IsValid(MainHUD)) return;
	const UMB_InteractionPromptWidget* InteractionPrompt = MainHUD->SetInteractionPromptWidget(true);
	InteractionPrompt->SetInteractionPhrase("interact");
}

void AMB_HabitatTerminalActor::OnExitInteractionRange(UMB_InteractionComponent* InteractionComponent)
{
	const APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	
	if (!IsValid(PlayerController)) return;
	AMB_MainHUD* MainHUD = PlayerController->GetHUD<AMB_MainHUD>();
	
	if (!IsValid(MainHUD)) return;
	MainHUD->SetInteractionPromptWidget(false);
}
