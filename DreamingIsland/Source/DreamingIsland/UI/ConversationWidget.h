// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/UserWidgetBase.h"
#include "Components/Image.h"
#include "ConversationWidget.generated.h"

/**
 * 
 */
UCLASS()
class DREAMINGISLAND_API UConversationWidget : public UUserWidgetBase
{
	GENERATED_BODY()
protected:
	virtual void NativeOnInitialized();
	virtual void NativePreConstruct();
	virtual void NativeConstruct();
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

	UFUNCTION()
	void OnHiddenUI();

protected:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UImage* ConversationMold;
};
