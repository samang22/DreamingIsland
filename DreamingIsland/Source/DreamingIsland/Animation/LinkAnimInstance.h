// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "LinkAnimInstance.generated.h"

UCLASS()
class DREAMINGISLAND_API ULinkAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	ULinkAnimInstance();

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY()
	class UPawnMovementComponent* MovementComponent;

	UPROPERTY()
	const class ULinkStatusComponent* StatusComponent;

	UPROPERTY(BlueprintReadOnly)
	double Speed = 0.0;

protected:
	bool bCanSlash = true;
public:
	void SetOnCanSlash() { bCanSlash = true; }
	void SetOffCanSlash() { bCanSlash = false; }

protected:
	UPROPERTY(BlueprintReadOnly)
	bool bIsWait = true;
	UPROPERTY(BlueprintReadOnly)
	bool bIsWalk = false;
	UPROPERTY(BlueprintReadOnly)
	bool bIsRun = false;
	UPROPERTY(BlueprintReadOnly)
	bool bIsCarry = false;

protected:
	UAnimMontage* AttackMontage;
	UAnimMontage* DieMontage;
	UAnimMontage* ItemCarryMontage;
	UAnimMontage* ItemGetMontage;

public:
	void PlayAttackMontage();
	void PlayDieMontage();
	void PlayItemCarryMontage();
	void PlayItemGetMontage();
};
