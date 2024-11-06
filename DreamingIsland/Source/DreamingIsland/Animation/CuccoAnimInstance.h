// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CuccoAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class DREAMINGISLAND_API UCuccoAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	UCuccoAnimInstance();

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY()
	const class UNPCStatusComponent* StatusComponent;

protected:
	UPROPERTY(BlueprintReadOnly)
	bool bIsWalk = false;
	UPROPERTY(BlueprintReadOnly)
	bool bIsWait = true;
	UPROPERTY(BlueprintReadOnly)
	bool bIsRun = false;
	UPROPERTY(BlueprintReadOnly)
	bool bIsLifted = false;
	UPROPERTY(BlueprintReadOnly)
	bool bIsThrown = false;

};
