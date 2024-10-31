// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/OctorokAnimInstance.h"
#include "Components/StatusComponent/MonsterStatusComponent.h"

UOctorokAnimInstance::UOctorokAnimInstance()
{
}

void UOctorokAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UOctorokAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (StatusComponent)
	{
		bIsWalk = StatusComponent->GetAnimStatus(MONSTER_BIT_WALK);
		bIsWait = StatusComponent->GetAnimStatus(MONSTER_BIT_WAIT);
	}
}
