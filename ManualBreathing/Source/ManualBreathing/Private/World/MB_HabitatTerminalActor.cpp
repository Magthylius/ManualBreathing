// Fill out your copyright notice in the Description page of Project Settings.


#include "World/MB_HabitatTerminalActor.h"

#include "Core/MB_MainGameState.h"
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
	FLogUtils::PrintScreen("In range with AMB_HabitatTerminalActor " + GetName());
}

void AMB_HabitatTerminalActor::OnExitInteractionRange(UMB_InteractionComponent* InteractionComponent)
{
	FLogUtils::PrintScreen("Left range of AMB_HabitatTerminalActor " + GetName());
}
