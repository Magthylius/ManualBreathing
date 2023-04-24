// Fill out your copyright notice in the Description page of Project Settings.


#include "Creatures/Components/MB_InteractionComponent.h"

#include "Components/ShapeComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "World/Interfaces/MB_InteractableInterface.h"

/* --- PUBLIC ---*/

UMB_InteractionComponent::UMB_InteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UMB_InteractionComponent::Interact()
{
	AActor* InteractionOwner = GetOwner();

	if (IsValid(InteractionDetector))
	{
		if (InteractablesInRange.IsEmpty()) return;
		
		if (InteractablesInRange.Num() > 1)
		{
			Algo::Sort(InteractablesInRange, [InteractionOwner](const AActor* A, const AActor* B)
				{ return InteractionOwner->GetSquaredDistanceTo(A) < InteractionOwner->GetSquaredDistanceTo(B); });
		}

		IMB_InteractableInterface* Interactable = Cast<IMB_InteractableInterface>(InteractablesInRange[0]);
		if (Interactable != nullptr)
		{
			Interactable->BeginInteraction();
		}
		
		return;
	}
	
	TArray<AActor*> OverlapResults;
	TArray<AActor*> IgnoredActors;
	
	IgnoredActors.Add(InteractionOwner);
	
	if (UKismetSystemLibrary::SphereOverlapActors(GetWorld(), InteractionOwner->GetActorLocation(),
		InteractionRadius, ObjectQueries, AActor::StaticClass(), IgnoredActors, OverlapResults))
	{
		if (OverlapResults.Num() > 1)
		{
			Algo::Sort(OverlapResults, [InteractionOwner](const AActor* A, const AActor* B)
				{ return InteractionOwner->GetSquaredDistanceTo(A) < InteractionOwner->GetSquaredDistanceTo(B); });
		}

		for (AActor* OverlappedActor : OverlapResults)
		{
			IMB_InteractableInterface* Interactable = Cast<IMB_InteractableInterface>(OverlappedActor);
			if (Interactable != nullptr)
			{
				Interactable->BeginInteraction();
				break;
			}
		}
	}
}

void UMB_InteractionComponent::SetupInteractionDetector(UShapeComponent* DetectorShape)
{
	if (IsValid(InteractionDetector))
	{
		InteractionDetector->OnComponentBeginOverlap.RemoveAll(this);
		InteractionDetector->OnComponentEndOverlap.RemoveAll(this);
	}

	InteractionDetector = DetectorShape;
	InteractionDetector->OnComponentBeginOverlap.AddUniqueDynamic(this, &UMB_InteractionComponent::OnInteractionBeginOverlap);
	InteractionDetector->OnComponentEndOverlap.AddUniqueDynamic(this, &UMB_InteractionComponent::OnInteractionEndOverlap);
}

/* --- PROTECTED ---*/

void UMB_InteractionComponent::OnInteractionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	IMB_InteractableInterface* Interactable = Cast<IMB_InteractableInterface>(OtherActor);
	if (Interactable != nullptr && !InteractablesInRange.Contains(OtherActor))
	{
		InteractablesInRange.Add(OtherActor);
		Interactable->OnEnterInteractionRange(this);
	}
}

void UMB_InteractionComponent::OnInteractionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	if (InteractablesInRange.Contains(OtherActor))
	{
		InteractablesInRange.Remove(OtherActor);

		IMB_InteractableInterface* Interactable = Cast<IMB_InteractableInterface>(OtherActor);
		if (Interactable != nullptr)
		{
			Interactable->OnExitInteractionRange(this);
		}
	}
}

