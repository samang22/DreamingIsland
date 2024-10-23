// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/MonsterAnimInstance.h"
#include "MoriblinAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class DREAMINGISLAND_API UMoriblinAnimInstance : public UMonsterAnimInstance
{
	GENERATED_BODY()

public:
	UMoriblinAnimInstance();

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(BlueprintReadOnly)
	bool bIsWalk = false;
	UPROPERTY(BlueprintReadOnly)
	bool bIsWait = true;
};
