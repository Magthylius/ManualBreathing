// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CheatManager.h"
#include "MB_CheatManager.generated.h"

/**
 * 
 */
UCLASS()
class MANUALBREATHING_API UMB_CheatManager : public UCheatManager
{
	GENERATED_BODY()

public:
	UFUNCTION(Exec)
	void LowOxy(bool bResetDeathTimeLeft = true) const;
};
