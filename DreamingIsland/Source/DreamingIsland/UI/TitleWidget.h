// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/UserWidgetBase.h"
#include "TitleWidget.generated.h"

class UImage;
UCLASS()
class DREAMINGISLAND_API UTitleWidget : public UUserWidgetBase
{
	GENERATED_BODY()

public:
	UTitleWidget();

protected:
	virtual void NativeOnInitialized() override;

protected:
	TObjectPtr<UImage> TitleVideoImage;
//protected:
//	TObjectPtr<UMaterialInstanceDynamic> MID = nullptr;
//
//public:
//	void SetMID_Texture(UTexture* _MediaTexture);
};
