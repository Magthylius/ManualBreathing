// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/MB_MainPlayerController.h"

#include "Core/MB_CheatManager.h"

AMB_MainPlayerController::AMB_MainPlayerController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	CheatClass = UMB_CheatManager::StaticClass();
}
