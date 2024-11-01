// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/UserWidgetBase.h"
#include "ChooseWidget.generated.h"

class UImage;
class UTextBlock;
UCLASS()
class DREAMINGISLAND_API UChooseWidget : public UUserWidgetBase
{
	GENERATED_BODY()
protected:
	virtual void NativeOnInitialized();
	virtual void NativePreConstruct();
	virtual void NativeConstruct();
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

public:
	UFUNCTION()
	void OnSetChoose(bool bIsYes);

protected:
	bool bIsYes = true;
public:
	bool GetIsYes() const { return bIsYes; }

protected:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UImage* YesImage;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UImage* NoImage;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UImage* YesHighLight;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UImage* NoHighLight;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UTextBlock* YesText;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UTextBlock* NoText;
};
