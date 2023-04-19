// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/MB_CheatManager.h"
#include "Creatures/MB_AstronautCharacter.h"

void UMB_CheatManager::LowOxy(const bool bResetDeathTimeLeft /* true */) const
{
	AMB_AstronautCharacter* Astronaut = Cast<AMB_AstronautCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	if (IsValid(Astronaut))
	{
		Astronaut->ForceLowOxy(bResetDeathTimeLeft);
	}
}
