// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "LinkAnimInstance.generated.h"

/**
 * 
 */
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
	UAnimMontage* AttackMontage;

public:
	UAnimMontage* GetAttackMontage() { return AttackMontage; }

public:
	void PlaySlashMontage();
	void StopSlashMontage();

protected:
	bool bCanSlash = true;
public:
	void SetOnSlash() { bCanSlash = true; }
	void SetOffSlash() { bCanSlash = false; }

protected:
	UPROPERTY(BlueprintReadOnly)
	bool bIsWait = true;
	UPROPERTY(BlueprintReadOnly)
	bool bIsWalk = false;
	UPROPERTY(BlueprintReadOnly)
	bool bIsRun = false;
	UPROPERTY(BlueprintReadOnly)
	bool bIsSlash = false;
	UPROPERTY(BlueprintReadOnly)
	bool bIsSlashHold = false;
	UPROPERTY(BlueprintReadOnly)
	bool bIsDeath = false;


};
