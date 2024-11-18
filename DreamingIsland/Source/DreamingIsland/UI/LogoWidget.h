// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/UserWidgetBase.h"
#include "LogoWidget.generated.h"

/**
 * 
 */
UCLASS()
class DREAMINGISLAND_API ULogoWidget : public UUserWidgetBase
{
	GENERATED_BODY()
public:
	ULogoWidget();

protected:
	virtual void NativeOnInitialized();
	virtual void NativePreConstruct();
	virtual void NativeConstruct();
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

protected:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UImage* LogoImage;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UImage* LogoShadeImage;

protected:
	bool bVisible = false;
	float LogoSinValue = 0.f;
public:
	void SetLogoVisible() { bVisible = true; }
};
