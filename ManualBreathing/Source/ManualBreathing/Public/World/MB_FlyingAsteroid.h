// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MB_FlyingAsteroid.generated.h"

UCLASS()
class MANUALBREATHING_API AMB_FlyingAsteroid : public AStaticMeshActor
{
	GENERATED_BODY()
	
public:	
	AMB_FlyingAsteroid();

protected:
	virtual void Tick(float DeltaTime) override;

private:
	/*UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "00 Components", meta = (AllowPrivateAccess))
	TObjectPtr<USceneComponent> SceneRoot;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "00 Components", meta = (AllowPrivateAccess))
	TObjectPtr<UStaticMeshComponent> StaticMesh;*/
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "00 Components", meta = (AllowPrivateAccess))
	//TObjectPtr<UParticleSystem> FlightParticles;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "01 Settings", meta = (AllowPrivateAccess))
	TObjectPtr<AActor> CrashTarget;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "01 Settings", meta = (AllowPrivateAccess))
	float TravelForce = 100.f;
};
