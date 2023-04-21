// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MB_HabitatActor.generated.h"

/**
 * 
 */
UCLASS()
class MANUALBREATHING_API AMB_HabitatActor : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	AMB_HabitatActor();

	void ActivateHabitat();
};
