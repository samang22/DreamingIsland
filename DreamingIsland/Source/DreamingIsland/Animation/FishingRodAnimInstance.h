// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "FishingRodAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class DREAMINGISLAND_API UFishingRodAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY()
	const class UFishingRodStatusComponent* StatusComponent;

protected:
	UPROPERTY(BlueprintReadOnly)
	bool bIsIdle = true;
	UPROPERTY(BlueprintReadOnly)
	bool bIsFighting = false;
	UPROPERTY(BlueprintReadOnly)
	bool bIsFishLost = false;
	UPROPERTY(BlueprintReadOnly)
	bool bIsThrowSt = false;
	UPROPERTY(BlueprintReadOnly)
	bool bIsThrowEd = false;
};
