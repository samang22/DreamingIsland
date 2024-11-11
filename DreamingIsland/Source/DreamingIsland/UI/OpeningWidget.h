// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/UserWidgetBase.h"
#include "OpeningWidget.generated.h"

class UImage;
class UMaterialInstanceDynamic;
class UTexture;
UCLASS()
class DREAMINGISLAND_API UOpeningWidget : public UUserWidgetBase
{
	GENERATED_BODY()
public:
	UOpeningWidget();

protected:
	virtual void NativeOnInitialized() override;

protected:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UImage> OpeningVideoImage;

//protected:
//	TObjectPtr<UMaterialInstanceDynamic> MID = nullptr;
//
//public:
//	void SetMID_Texture(UTexture* _MediaTexture);

};
