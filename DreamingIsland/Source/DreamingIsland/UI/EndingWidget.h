// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/UserWidgetBase.h"
#include "EndingWidget.generated.h"

class UImage;
UCLASS()
class DREAMINGISLAND_API UEndingWidget : public UUserWidgetBase
{
	GENERATED_BODY()

public:
	UEndingWidget();

protected:
	virtual void NativeOnInitialized() override;

protected:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UImage> EndingVideoImage;
//protected:
//	TObjectPtr<UMaterialInstanceDynamic> MID = nullptr;
//
//public:
//	void SetMID_Texture(UTexture* _MediaTexture);
};
