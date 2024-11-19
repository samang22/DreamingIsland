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
	//FTimerDelegate TimerDelegate;
	//TimerDelegate.BindUFunction(this, FName("OnHiddenUI"));  // C++에서 함수 이름을 사용할 때는 FName을 사용

	//// 타이머 설정
	//GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, Seconds, false);

	UKismetSystemLibrary::K2_SetTimer(this, TEXT("OnHiddenUI"), Seconds, false);
}
