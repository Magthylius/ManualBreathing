// Fill out your copyright notice in the Description page of Project Settings.


#include "World/MB_HabitatTerminalActor.h"

#include "Core/MB_MainGameState.h"
#include "Core/MB_MainHUD.h"
#include "Kismet/GameplayStatics.h"
#include "Shell/Utils/LogUtils.h"

AMB_HabitatTerminalActor::AMB_HabitatTerminalActor()
{
	GetStaticMeshComponent()->SetGenerateOverlapEvents(true);
}

void AMB_HabitatTerminalActor::BeginInteraction()
{
	AMB_MainGameState* GameState = GetWorld()->GetGameState<AMB_MainGameState>();
	GameState->EndGame();
}

void AMB_HabitatTerminalActor::OnEnterInteractionRange(UMB_InteractionComponent* InteractionComponent)
{
	AMB_MainHUD* MainHUD = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD<AMB_MainHUD>();
	const UMB_InteractionPromptWidget* InteractionPrompt = MainHUD->SetInteractionPrompt(true);
	InteractionPrompt->SetInteractionPhrase("interact");
}

void AMB_HabitatTerminalActor::OnExitInteractionRange(UMB_InteractionComponent* InteractionComponent)
{
	AMB_MainHUD* MainHUD = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD<AMB_MainHUD>();
	MainHUD->SetInteractionPrompt(false);
}
