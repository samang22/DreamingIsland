// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/UserWidgetBase.h"
#include "RupeeWidget.generated.h"

/**
 * 
 */
UCLASS()
class DREAMINGISLAND_API URupeeWidget : public UUserWidgetBase
{
	GENERATED_BODY()
protected:
	virtual void NativeOnInitialized();
	virtual void NativePreConstruct();
	virtual void NativeConstruct();
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

public:
	UFUNCTION()
	void OnSetRupeeNum(int RupeeNum);

protected:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UImage* RupeeImage;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTextBlock* RupeeNumText;

protected:
	int DesiredRupeeNum = 0;
	int CurrentRupeeNum = 0;
};
