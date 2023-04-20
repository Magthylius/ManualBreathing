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
	void LowOxyReset(const bool bResetDeathTimeLeft = true) const;
	UFUNCTION(Exec)
	void LowOxy(const float DeathTimeLeft) const;
	UFUNCTION(Exec)
	void GodMode(const bool bEnable = true) const;
};
