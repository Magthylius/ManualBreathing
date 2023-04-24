// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/MB_MainPlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "World/MB_EarthActor.h"

void AMB_MainPlayerStart::LookAtEarth()
{
	const AMB_EarthActor* EarthActor = Cast<AMB_EarthActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AMB_EarthActor::StaticClass()));
	if (IsValid(EarthActor))
	{
		const FRotator EarthDirection = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), EarthActor->GetActorLocation());
		SetActorRotation(EarthDirection);
	}
}
