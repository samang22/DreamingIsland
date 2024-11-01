// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ChooseWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Kismet/KismetSystemLibrary.h"

void UChooseWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UChooseWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UChooseWidget::NativeConstruct()
{
	Super::NativeConstruct();

	APawn* Pawn = GetOwningPawn();
	SetVisibility(ESlateVisibility::Hidden);
}

void UChooseWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	YesHighLight->SetVisibility(bIsYes ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	NoHighLight->SetVisibility(!bIsYes ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}

void UChooseWidget::OnSetChoose(bool _bIsYes)
{
	bIsYes = _bIsYes;
}

