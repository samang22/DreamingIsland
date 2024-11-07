// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/NPCAnimInstance.h"
#include "CuccoAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class DREAMINGISLAND_API UCuccoAnimInstance : public UNPCAnimInstance
{
	GENERATED_BODY()
public:
	UCuccoAnimInstance();

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};
