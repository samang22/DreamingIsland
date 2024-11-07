// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/CuccoAnimInstance.h"
#include "Actors/NPC/Cucco.h"
#include "Components/StatusComponent/NPCStatusComponent.h"
#include "Misc/Utils.h"

UCuccoAnimInstance::UCuccoAnimInstance()
{
}

void UCuccoAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UCuccoAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
}
