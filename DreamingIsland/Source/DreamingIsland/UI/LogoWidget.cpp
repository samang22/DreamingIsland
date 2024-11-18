// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/LogoWidget.h"
#include "Components/Image.h"

ULogoWidget::ULogoWidget()
{
}

void ULogoWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void ULogoWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void ULogoWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//SetVisibility(ESlateVisibility::Hidden);
}

void ULogoWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);


	if (bVisible)
	{
		LogoSinValue += InDeltaTime;
		float Opacity = FMath::Sin(LogoSinValue);
		Opacity = (Opacity + 1) * 0.5f;

		LogoImage->SetOpacity(Opacity);
		LogoShadeImage->SetOpacity(Opacity);
	}

}

