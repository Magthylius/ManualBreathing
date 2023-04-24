// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/MB_EndScreenWidget.h"
#include "Kismet/KismetStringLibrary.h"

void UMB_EndScreenWidget::SetOutcome(const FMB_EndScreenOutcome Outcome)
{
	TitleTextBlock->SetRenderOpacity(0.f);
	TimeTakenTextBlock->SetRenderOpacity(0.f);
	OxygenBreathedTextBlock->SetRenderOpacity(0.f);
	BreathsTakenTextBlock->SetRenderOpacity(0.f);
	
	bShowTitle = false;
	bShowTimeTaken = false;
	bShowOxygenBreathed = false;
	bShowBreathsTaken = false;

	TitleTextBlock->SetText(FText::FromString(Outcome.bPlayerHasWon ? WinningText : LosingText));
	TitleTextBlock->SetColorAndOpacity(Outcome.bPlayerHasWon ? WinningColor : LosingColor);

	const FString TimeTakenText = "Time Taken: " + UKismetStringLibrary::TimeSecondsToString(Outcome.TimeTaken);
	const FString OxygenBreathedText = "Oxygen Breathed: " + FString::SanitizeFloat(Outcome.OxygenBreathed) + "cm^3";
	const FString BreathsTakenText = "Breaths Taken: " + FString::FromInt(Outcome.BreathsTaken);
	TimeTakenTextBlock->SetText(FText::FromString(TimeTakenText));
	OxygenBreathedTextBlock->SetText(FText::FromString(OxygenBreathedText));
	BreathsTakenTextBlock->SetText(FText::FromString(BreathsTakenText));

	constexpr float StartTime = 1.f;
	GetWorld()->GetTimerManager().SetTimer(ShowTitleHandle, this, &UMB_EndScreenWidget::StartShowTitle, StartTime, false, 0.f);
	GetWorld()->GetTimerManager().SetTimer(ShowTimeHandle, this, &UMB_EndScreenWidget::StartShowTimeTaken, StartTime, false, 1.f);
	GetWorld()->GetTimerManager().SetTimer(ShowOxygenBreathedHandle, this, &UMB_EndScreenWidget::StartShowOxygenBreathed, StartTime, false, 1.5f);
	GetWorld()->GetTimerManager().SetTimer(ShowBreathsTakenHandle, this, &UMB_EndScreenWidget::StartShowBreathsTaken, StartTime, false, 2.f);
}

void UMB_EndScreenWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	const float RenderOpacitySpeed = OpacitySpeed * InDeltaTime;
	
	if (bShowTitle)
	{
		TitleTextBlock->SetRenderOpacity(FMath::Lerp(TitleTextBlock->GetRenderOpacity(), 1.f, RenderOpacitySpeed));
	}

	if (bShowTimeTaken)
	{
		TimeTakenTextBlock->SetRenderOpacity(FMath::Lerp(TimeTakenTextBlock->GetRenderOpacity(), 1.f, RenderOpacitySpeed));
	}

	if (bShowOxygenBreathed)
	{
		OxygenBreathedTextBlock->SetRenderOpacity(FMath::Lerp(OxygenBreathedTextBlock->GetRenderOpacity(), 1.f, RenderOpacitySpeed));
	}

	if (bShowBreathsTaken)
	{
		BreathsTakenTextBlock->SetRenderOpacity(FMath::Lerp(BreathsTakenTextBlock->GetRenderOpacity(), 1.f, RenderOpacitySpeed));
	}
}
