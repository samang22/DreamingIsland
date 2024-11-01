// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "DefaultHUD.generated.h"

/**
 * 
 */
UCLASS()
class DREAMINGISLAND_API ADefaultHUD : public AHUD
{
	GENERATED_BODY()

public:
	ADefaultHUD();

protected:
	virtual void BeginPlay() override;

protected:
	class UConversationWidget* Widget;
	class URupeeWidget* RupeeWidget;
	class UChooseWidget* ChooseWidget;
public:
	void OnShowConversationWidget();
	void OnShowChooseWidget();
	void OnShowRupeeWidget();
public:
	UFUNCTION()
	void OnHideConversationWidget();
	UFUNCTION()
	void OnHideChooseWidget();
	UFUNCTION()
	void OnHideRupeeWidget();
public:
	void OnDelayHideConversationWidget(float Seconds);
	void OnDelayHideChooseWidget(float Seconds);
	void OnDelayHideRupeeWidget(float Seconds);


public:
	void OnSetStringToConversation(FString Speaker, FString String);
	void OnSetRupeeNum(int RupeeNum);
	void OnSetSelection(bool bSelection);
	bool GetSelection();

public:
	bool GetIsChooseWidgetVisible();
};
