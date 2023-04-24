// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "Interfaces/MB_InteractableInterface.h"
#include "MB_HabitatTerminalActor.generated.h"

/**
 * 
 */
UCLASS()
class MANUALBREATHING_API AMB_HabitatTerminalActor : public AStaticMeshActor, public IMB_InteractableInterface
{
	GENERATED_BODY()

public:
	AMB_HabitatTerminalActor();
	
	virtual void BeginInteraction() override;
	virtual void OnEnterInteractionRange(UMB_InteractionComponent* InteractionComponent) override;
	virtual void OnExitInteractionRange(UMB_InteractionComponent* InteractionComponent) override;
};
