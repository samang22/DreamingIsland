// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AlbatossAnimInstance.h"
#include "Components/StatusComponent/MonsterStatusComponent.h"

UAlbatossAnimInstance::UAlbatossAnimInstance()
{
}

void UAlbatossAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UAlbatossAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (StatusComponent)
	{
		bIsRush = StatusComponent->GetAnimStatus(MONSTER_BIT_RUSH);
		bIsWait = StatusComponent->GetAnimStatus(MONSTER_BIT_WAIT);
	}
}

