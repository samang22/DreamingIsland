// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/HinoxAnimInstance.h"
#include "Components/StatusComponent/MonsterStatusComponent.h"
#include "Misc/Utils.h"

UHinoxAnimInstance::UHinoxAnimInstance()
{
}

void UHinoxAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UHinoxAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (StatusComponent)
	{
		bIsWait = StatusComponent->GetAnimStatus(MONSTER_BIT_WAIT);
		bIsWalk = StatusComponent->GetAnimStatus(MONSTER_BIT_WALK);
		bIsRush = StatusComponent->GetAnimStatus(MONSTER_BIT_RUSH);
	}
}
