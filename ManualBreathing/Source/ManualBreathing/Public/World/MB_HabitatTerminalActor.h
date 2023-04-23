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
	virtual void BeginInteraction() override;
};
