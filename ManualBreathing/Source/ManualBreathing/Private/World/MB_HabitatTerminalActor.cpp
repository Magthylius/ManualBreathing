// Fill out your copyright notice in the Description page of Project Settings.


#include "World/MB_HabitatTerminalActor.h"

#include "Shell/Utils/LogUtils.h"

void AMB_HabitatTerminalActor::BeginInteraction()
{
	FLogUtils::PrintScreen("Interacted with AMB_HabitatTerminalActor");
}
