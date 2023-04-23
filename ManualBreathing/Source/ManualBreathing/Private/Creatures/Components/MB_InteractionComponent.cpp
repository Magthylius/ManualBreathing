// Fill out your copyright notice in the Description page of Project Settings.


#include "Creatures/Components/MB_InteractionComponent.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Shell/Utils/LogUtils.h"
#include "World/Interfaces/MB_InteractableInterface.h"

UMB_InteractionComponent::UMB_InteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UMB_InteractionComponent::Interact()
{
	TArray<AActor*> OverlapResults;
	TArray<AActor*> IgnoredActors;

	AActor* InteractionOwner = GetOwner();
	
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


void UMB_InteractionComponent::BeginPlay()
{
	Super::BeginPlay();
}

