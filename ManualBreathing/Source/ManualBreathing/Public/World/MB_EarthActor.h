// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MB_EarthActor.generated.h"

/**
 * 
 */
UCLASS()
class MANUALBREATHING_API AMB_EarthActor : public AStaticMeshActor
{
	GENERATED_BODY()
public:
	AMB_EarthActor(const FObjectInitializer& ObjectInitializer);

	FORCEINLINE UStaticMeshComponent* GetAtmosphere() const { return AtmosphereComponent; }
	FORCEINLINE UStaticMeshComponent* GetClouds() const { return CloudsComponent; }
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "00 Components", meta = (AllowPrivateAccess))
	TObjectPtr<UStaticMeshComponent> AtmosphereComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "00 Components", meta = (AllowPrivateAccess))
	TObjectPtr<UStaticMeshComponent> CloudsComponent;
};
