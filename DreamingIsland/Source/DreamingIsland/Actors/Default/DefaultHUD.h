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
	class UChooseWidget* ChooseWidget;
	class URupeeWidget* RupeeWidget;
	class UArrowWidget* ArrowWidget;
	class UBombWidget* BombWidget;
	class UCuccoQuestWidget* CuccoQuestWidget;
public:
	void OnShowConversationWidget();
	void OnShowChooseWidget();
	void OnShowRupeeWidget();
	void OnShowArrowWidget();
	void OnShowBombWidget();
	void OnShowCuccoQuestWidget();

public:
	UFUNCTION()
	void OnHideConversationWidget();
	UFUNCTION()
	void OnHideChooseWidget();
	UFUNCTION()
	void OnHideRupeeWidget();
	UFUNCTION()
	void OnHideArrowWidget();
	UFUNCTION()
	void OnHideBombWidget();
	UFUNCTION()
	void OnHideCuccoQuestWidget();

public:
	void OnDelayHideConversationWidget(float Seconds);
	void OnDelayHideChooseWidget(float Seconds);
	void OnDelayHideRupeeWidget(float Seconds);
	void OnDelayHideArrowWidget(float Seconds);
	void OnDelayHideBombWidget(float Seconds);
	void OnDelayHideCuccoQuestWidget(float Seconds);


public:
	void OnSetStringToConversation(FString Speaker, FString String);
	void OnSetRupeeNum(int RupeeNum);
	void OnSetArrowNum(int ArrowNum);
	void OnSetBombNum(int BombNum);
	void OnSetCuccoNum(int CuccoNum);
	void OnSetSelection(bool bSelection);
	bool GetSelection();

public:
	bool GetIsChooseWidgetVisible();
};
