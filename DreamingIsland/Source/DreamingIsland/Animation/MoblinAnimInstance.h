// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/MonsterAnimInstance.h"
#include "MoblinAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class DREAMINGISLAND_API UMoblinAnimInstance : public UMonsterAnimInstance
{
	GENERATED_BODY()

public:
	UMoblinAnimInstance();

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(BlueprintReadOnly)
	bool bIsWalk = false;
	UPROPERTY(BlueprintReadOnly)
	bool bIsWait = true;
	UPROPERTY(BlueprintReadOnly)
	bool bIsHoldingSpear = false;
};
