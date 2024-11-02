// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ArrowWidget.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

#define INCREASE_DECREASE_NUM 1

void UArrowWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UArrowWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UArrowWidget::NativeConstruct()
{
	Super::NativeConstruct();

	APawn* Pawn = GetOwningPawn();
	SetVisibility(ESlateVisibility::Hidden);
}

void UArrowWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	bool bShowWidget = false;
	if (DesiredArrowNum < CurrentArrowNum)
	{
		bShowWidget = true;
		CurrentArrowNum -= INCREASE_DECREASE_NUM;
		if (DesiredArrowNum > CurrentArrowNum)
		{
			CurrentArrowNum = DesiredArrowNum;
		}
	}
	else if (DesiredArrowNum > CurrentArrowNum)
	{
		bShowWidget = true;
		CurrentArrowNum += INCREASE_DECREASE_NUM;
		if (DesiredArrowNum < CurrentArrowNum)
		{
			CurrentArrowNum = DesiredArrowNum;
		}
	}

	FText ArrowText = FText::AsNumber(CurrentArrowNum);
	ArrowNumText->SetText(ArrowText);

	if (bShowWidget == true)
	{
		SetVisibility(ESlateVisibility::Visible);
		OnDealyHidden(2.f);
	}
}

void UArrowWidget::OnSetArrowNum(int ArrowNum)
{
	DesiredArrowNum = ArrowNum;
}
