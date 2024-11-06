// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StatusComponent/StatusComponent.h"
#include "MonsterStatusComponent.generated.h"





UCLASS()
class DREAMINGISLAND_API UMonsterStatusComponent : public UStatusComponent
{
	GENERATED_BODY()
	
public:
	UMonsterStatusComponent();

protected:
	UPROPERTY()
	uint8 MonsterAnimationStatus;

public:
	void SetOnAnimationStatus(uint8 InBit);
	void SetOffAnimationStatus(uint8 InBit);

public:
	UFUNCTION()
	bool GetAnimStatus(uint8 InBit) const;

protected:
	UPROPERTY(BlueprintReadOnly)
	bool bIsHoldingWeapon = false;

public:
	UFUNCTION(BlueprintCallable)
	void SetHoldingWeaponOn() { bIsHoldingWeapon = true; }
	UFUNCTION(BlueprintCallable)
	void SetHoldingWeaponOff() { bIsHoldingWeapon = false; }
};
