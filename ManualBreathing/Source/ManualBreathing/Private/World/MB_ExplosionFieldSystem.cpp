// Fill out your copyright notice in the Description page of Project Settings.


#include "World/MB_ExplosionFieldSystem.h"

#include "Field/FieldSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ManualBreathing/Public/Shell/Utils/LogUtils.h"

/* --- PUBLIC ---*/

AMB_ExplosionFieldSystem::AMB_ExplosionFieldSystem()
{
	SphereDetector = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	SphereDetector->SetupAttachment(RootComponent);
	SphereDetector->InitSphereRadius(200.f);

	RadialFalloff = CreateDefaultSubobject<URadialFalloff>("RadialFalloffComponent");
}

void AMB_ExplosionFieldSystem::CreateExplosion() const
{
	if (ExplosionParticles == nullptr || !IsValid(ExplosionSoundBase))
	{
		UE_LOG(LogMBWorld, Error, TEXT("AMB_ExplosionFieldSystem: Invalid setup!"));
		return;
	}
	
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionParticles, GetActorTransform());
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), ExplosionSoundBase, GetActorLocation());

	//! NOTE: Magnitude is the GMC's damage threshold
	RadialFalloff->SetRadialFalloff(500000.0f, 0.f, 1.f, 0.f, SphereDetector->GetScaledSphereRadius(), SphereDetector->GetComponentLocation(), EFieldFalloffType::Field_FallOff_None);

	GetFieldSystemComponent()->ApplyPhysicsField(true, EFieldPhysicsType::Field_ExternalClusterStrain, nullptr, RadialFalloff);
}
