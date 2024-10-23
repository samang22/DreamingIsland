// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/MoblinAnimInstance.h"
#include "Components/MonsterStatusComponent.h"

UMoblinAnimInstance::UMoblinAnimInstance()
{
}

void UMoblinAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UMoblinAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (StatusComponent)
	{
		bIsWait = StatusComponent->GetAnimStatus(MONSTER_BIT_WAIT);
		bIsWalk = StatusComponent->GetAnimStatus(MONSTER_BIT_WALK);
	}
}
