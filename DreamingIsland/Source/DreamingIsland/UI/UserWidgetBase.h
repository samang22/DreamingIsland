// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UserWidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class DREAMINGISLAND_API UUserWidgetBase : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeOnInitialized();
	virtual void NativePreConstruct();
	virtual void NativeConstruct();
	void SetOwningPawn(APawn* NewPawn) { OwningPawn = NewPawn; }
	APawn* GetOwningPawn() const { return OwningPawn; }
protected:
	UPROPERTY()
	APawn* OwningPawn = nullptr;

public:
	UFUNCTION()
	void OnShow();
	UFUNCTION()
	void OnHidden();
	UFUNCTION()
	void OnDealyHidden(float Seconds);

};
