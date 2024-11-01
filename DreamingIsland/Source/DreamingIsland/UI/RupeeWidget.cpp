// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RupeeWidget.h"
#include "Kismet/KismetSystemLibrary.h"

#define INCREASE_DECREASE_NUM 3

void URupeeWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void URupeeWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void URupeeWidget::NativeConstruct()
{
	Super::NativeConstruct();

	APawn* Pawn = GetOwningPawn();
	SetVisibility(ESlateVisibility::Hidden);
}

void URupeeWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	bool bShowWidget = false;
	if (DesiredRupeeNum < CurrentRupeeNum)
	{
		bShowWidget = true;
		CurrentRupeeNum -= INCREASE_DECREASE_NUM;
		if (DesiredRupeeNum > CurrentRupeeNum)
		{
			CurrentRupeeNum = DesiredRupeeNum;
		}
	}
	else if (DesiredRupeeNum > CurrentRupeeNum)
	{
		bShowWidget = true;
		CurrentRupeeNum += INCREASE_DECREASE_NUM;
		if (DesiredRupeeNum < CurrentRupeeNum)
		{
			CurrentRupeeNum = DesiredRupeeNum;
		}
	}

	FText RupeeText = FText::AsNumber(CurrentRupeeNum);
	RupeeNumText->SetText(RupeeText);

	if (bShowWidget == true)
	{
		SetVisibility(ESlateVisibility::Visible);
		UKismetSystemLibrary::K2_SetTimer(this, TEXT("OnHiddenUI"), 2.f, false);
	}
}

void URupeeWidget::OnHiddenUI()
{
	SetVisibility(ESlateVisibility::Hidden);
}

void URupeeWidget::OnSetRupeeNum(int RupeeNum)
{
	DesiredRupeeNum = RupeeNum;

	SetVisibility(ESlateVisibility::Visible);
	UKismetSystemLibrary::K2_SetTimer(this, TEXT("OnHiddenUI"), 2.f, false);
}

void URupeeWidget::OnShowRupeeNum()
{
	SetVisibility(ESlateVisibility::Visible);
	UKismetSystemLibrary::K2_SetTimer(this, TEXT("OnHiddenUI"), 2.f, false);
}
