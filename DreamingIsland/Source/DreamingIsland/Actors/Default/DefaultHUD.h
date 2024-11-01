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
public:
	void OnSetStringToConversation(FString Speaker, FString String);
	void OnSetRupeeNum(int RupeeNum);
};
