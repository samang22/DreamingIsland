// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/UserWidgetBase.h"
#include "ArrowWidget.generated.h"

/**
 * 
 */
UCLASS()
class DREAMINGISLAND_API UArrowWidget : public UUserWidgetBase
{
	GENERATED_BODY()
protected:
	virtual void NativeOnInitialized();
	virtual void NativePreConstruct();
	virtual void NativeConstruct();
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

public:
	UFUNCTION()
	void OnSetArrowNum(int RupeeNum);

protected:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UImage* ArrowImage;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTextBlock* ArrowNumText;

protected:
	int DesiredArrowNum = 0;
	int CurrentArrowNum = 0;
};
