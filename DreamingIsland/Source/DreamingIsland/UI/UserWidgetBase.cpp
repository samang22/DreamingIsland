// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UserWidgetBase.h"
#include "Kismet/KismetSystemLibrary.h"

void UUserWidgetBase::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UUserWidgetBase::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UUserWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();
}

void UUserWidgetBase::OnShow()
{
	SetVisibility(ESlateVisibility::Visible);
}

void UUserWidgetBase::OnHidden()
{
	SetVisibility(ESlateVisibility::Hidden);
}

void UUserWidgetBase::OnDealyHidden(float Seconds)
{
	UKismetSystemLibrary::K2_SetTimer(this, TEXT("OnHiddenUI"), Seconds, false);
}
