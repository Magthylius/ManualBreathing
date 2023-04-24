// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Actor.h"
#include "MB_TitleWidgetActor.generated.h"

UCLASS()
class MANUALBREATHING_API AMB_TitleWidgetActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AMB_TitleWidgetActor();

	void SetWidgetHidden(const bool bWidgetHidden) const;
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "00 Components", meta = (AllowPrivateAccess))
	TObjectPtr<USceneComponent> SceneRoot;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "00 Components", meta = (AllowPrivateAccess))
	TObjectPtr<UWidgetComponent> WidgetComponent;
};
