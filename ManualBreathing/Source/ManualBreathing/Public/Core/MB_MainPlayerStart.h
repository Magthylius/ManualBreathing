// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerStart.h"
#include "MB_MainPlayerStart.generated.h"

/**
 * 
 */
UCLASS()
class MANUALBREATHING_API AMB_MainPlayerStart : public APlayerStart
{
	GENERATED_BODY()

public:
	UFUNCTION(CallInEditor)
	void LookAtEarth();
};
