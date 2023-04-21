// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MB_HabitatActor.h"
#include "Engine/StaticMeshActor.h"
#include "MB_HabitatWaypointActor.generated.h"

/**
 * 
 */
UCLASS()
class MANUALBREATHING_API AMB_HabitatWaypointActor : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	AMB_HabitatWaypointActor();

protected:
	virtual void Tick(float DeltaSeconds) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "00 Components", meta = (AllowPrivateAccess))
	TObjectPtr<UStaticMeshComponent> PointerStaticMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "02 Runtime Data", meta = (AllowPrivateAccess))
	TObjectPtr<AMB_HabitatActor> TrueHabitat;
};
