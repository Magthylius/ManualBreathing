// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MB_InteractableInterface.generated.h"

class UMB_InteractionComponent;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UMB_InteractableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface meant to be implemented in actors
 */
class MANUALBREATHING_API IMB_InteractableInterface
{
	GENERATED_BODY()

public:
	virtual void BeginInteraction() = 0;

	virtual void OnEnterInteractionRange(UMB_InteractionComponent* InteractionComponent) { }
	virtual void OnExitInteractionRange(UMB_InteractionComponent* InteractionComponent) { }
};
