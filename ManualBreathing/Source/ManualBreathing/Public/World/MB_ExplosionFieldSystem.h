// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "Field/FieldSystemActor.h"
#include "Field/FieldSystemObjects.h"
#include "MB_ExplosionFieldSystem.generated.h"

/**
 * 
 */
UCLASS()
class MANUALBREATHING_API AMB_ExplosionFieldSystem : public AFieldSystemActor
{
	GENERATED_BODY()

public:
	AMB_ExplosionFieldSystem();

	UFUNCTION(BlueprintCallable)
	void CreateExplosion() const;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "00 Components", meta = (AllowPrivateAccess))
	TObjectPtr<USphereComponent> SphereDetector;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "00 Components", meta = (AllowPrivateAccess))
	TObjectPtr<URadialFalloff> RadialFalloff;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "01 Settings", meta= (AllowPrivateAccess))
	TObjectPtr<UParticleSystem> ExplosionParticles;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "01 Settings", meta= (AllowPrivateAccess))
	TObjectPtr<USoundBase> ExplosionSoundBase;
};
