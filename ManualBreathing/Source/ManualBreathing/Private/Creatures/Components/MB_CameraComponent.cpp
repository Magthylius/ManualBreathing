// Fill out your copyright notice in the Description page of Project Settings.


#include "Creatures/Components/MB_CameraComponent.h"

/* --- PUBLIC ---*/

void UMB_CameraComponent::SetTargetFieldOfField(const float InTargetFOV)
{
	if (InTargetFOV != TargetFieldOfView)
	{
		bFieldOfViewDirty = true;
		TargetFieldOfView = InTargetFOV;
	}
}

/* --- PROTECTED ---*/

void UMB_CameraComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bFieldOfViewDirty)
	{
		FieldOfView = FMath::Lerp(FieldOfView, TargetFieldOfView, FieldOfViewSpeed * DeltaTime);
		
		if (FMath::Abs(TargetFieldOfView - FieldOfView) < 0.0001f)
		{
			FieldOfView = TargetFieldOfView;
			bFieldOfViewDirty = false;
		}
	}
}
