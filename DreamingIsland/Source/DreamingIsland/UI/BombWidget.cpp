// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BombWidget.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

#define INCREASE_DECREASE_NUM 1

void UBombWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UBombWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UBombWidget::NativeConstruct()
{
	Super::NativeConstruct();

	APawn* Pawn = GetOwningPawn();
	SetVisibility(ESlateVisibility::Hidden);
}

void UBombWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	bool bShowWidget = false;
	if (DesiredBombNum < CurrentBombNum)
	{
		bShowWidget = true;
		CurrentBombNum -= INCREASE_DECREASE_NUM;
		if (DesiredBombNum > CurrentBombNum)
		{
			CurrentBombNum = DesiredBombNum;
		}
	}
	else if (DesiredBombNum > CurrentBombNum)
	{
		bShowWidget = true;
		CurrentBombNum += INCREASE_DECREASE_NUM;
		if (DesiredBombNum < CurrentBombNum)
		{
			CurrentBombNum = DesiredBombNum;
		}
	}

	FText BombText = FText::AsNumber(CurrentBombNum);
	BombNumText->SetText(BombText);

	if (bShowWidget == true)
	{
		SetVisibility(ESlateVisibility::Visible);
		OnDealyHidden(2.f);
	}
}

void UBombWidget::OnSetBombNum(int BombNum)
{
	DesiredBombNum = BombNum;
}
