// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CraneButtonAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class DREAMINGISLAND_API UCraneButtonAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UCraneButtonAnimInstance();

protected:
	UAnimMontage* ButtonAMontage;
	UAnimMontage* ButtonXMontage;

public:
	void PlayMontage_ButtonAOn();
	void PlayMontage_ButtonXOn();
};
