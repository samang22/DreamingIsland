// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/MonsterAnimInstance.h"
#include "OctorokAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class DREAMINGISLAND_API UOctorokAnimInstance : public UMonsterAnimInstance
{
	GENERATED_BODY()
public:
	UOctorokAnimInstance();

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(BlueprintReadOnly)
	bool bIsWalk = false;
	UPROPERTY(BlueprintReadOnly)
	bool bIsWait = true;
};