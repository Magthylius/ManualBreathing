// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MB_MainPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MANUALBREATHING_API AMB_MainPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AMB_MainPlayerController(const FObjectInitializer& ObjectInitializer);
};
