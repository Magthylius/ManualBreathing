// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MB_MainHUD.generated.h"

/**
 * 
 */
UCLASS()
class MANUALBREATHING_API AMB_MainHUD : public AHUD
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "01 Settings", meta = (AllowPrivateAccess))
	TSubclassOf<UUserWidget> HelmetHUD;
};
