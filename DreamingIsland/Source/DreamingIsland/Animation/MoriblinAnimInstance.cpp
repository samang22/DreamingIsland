// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/MoriblinAnimInstance.h"
#include "Components/StatusComponent/MonsterStatusComponent.h"

UMoriblinAnimInstance::UMoriblinAnimInstance()
{
}

void UMoriblinAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UMoriblinAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (StatusComponent)
	{
		bIsWait = StatusComponent->GetAnimStatus(MONSTER_BIT_WAIT);
		bIsWalk = StatusComponent->GetAnimStatus(MONSTER_BIT_WALK);
	}
}
