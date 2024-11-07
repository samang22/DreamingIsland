// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/UserWidgetBase.h"
#include "CuccoQuestWidget.generated.h"

UCLASS()
class DREAMINGISLAND_API UCuccoQuestWidget : public UUserWidgetBase
{
	GENERATED_BODY()

public:
	UCuccoQuestWidget();

protected:
	virtual void NativeOnInitialized();
	virtual void NativePreConstruct();
	virtual void NativeConstruct();
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

public:
	UFUNCTION()
	void OnSetCuccoNum(int CuccoNum);

protected:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UImage* CuccoImage;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTextBlock* CurrentCuccoNumText;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTextBlock* MaxCuccoNumText;

protected:
	int CurrentCuccoNum = 0;
	int MaxCuccoNum;
};
