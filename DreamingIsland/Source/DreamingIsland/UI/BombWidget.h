// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/UserWidgetBase.h"
#include "BombWidget.generated.h"

/**
 * 
 */
UCLASS()
class DREAMINGISLAND_API UBombWidget : public UUserWidgetBase
{
	GENERATED_BODY()
protected:
	virtual void NativeOnInitialized();
	virtual void NativePreConstruct();
	virtual void NativeConstruct();
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

public:
	UFUNCTION()
	void OnSetBombNum(int BombNum);

protected:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UImage* BombImage;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTextBlock* BombNumText;

protected:
	int DesiredBombNum = 0;
	int CurrentBombNum = 0;
};
