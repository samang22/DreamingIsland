// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "FishAnimInstance.generated.h"

class UPawnMovementComponent;
UCLASS()
class DREAMINGISLAND_API UFishAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY()
	TObjectPtr<UPawnMovementComponent> MovementComponent;

	UPROPERTY()
	const class UFishStatusComponent* StatusComponent;

	UPROPERTY(BlueprintReadOnly)
	double Speed = 0.0;


protected:
	UPROPERTY(BlueprintReadOnly)
	bool bIsWait = true;
	UPROPERTY(BlueprintReadOnly)
	bool bIsPokeWaiting = false;
	UPROPERTY(BlueprintReadOnly)
	bool bIsCatch = false;
	UPROPERTY(BlueprintReadOnly)
	bool bIsGet = false;
};
