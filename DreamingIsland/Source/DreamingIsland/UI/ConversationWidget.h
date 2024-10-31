// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/UserWidgetBase.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
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
public:
	UFUNCTION()
	void OnSetStringToConversation(FString Speaker, FString String);

protected:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UImage* ConversationMold;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UTextBlock* Speaker;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UTextBlock* TextBlock;
};
