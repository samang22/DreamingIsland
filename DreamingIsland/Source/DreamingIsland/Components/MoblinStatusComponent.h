// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/MonsterStatusComponent.h"
#include "MoblinStatusComponent.generated.h"

UCLASS()
class DREAMINGISLAND_API UMoblinStatusComponent : public UMonsterStatusComponent
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadOnly)
	bool bIsHoldingSpear = false;

public:
	UFUNCTION(BlueprintCallable)
	void SetMoblinSpearOn() { bIsHoldingSpear = true; }
	UFUNCTION(BlueprintCallable)
	void SetMoblinSpearOff() { bIsHoldingSpear = false; }
};
