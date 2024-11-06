// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/StatusComponent/MonsterStatusComponent.h"

#include "Misc/Utils.h"

UMonsterStatusComponent::UMonsterStatusComponent()
{
	SetOnAnimationStatus(MONSTER_BIT_WAIT);
}

void UMonsterStatusComponent::SetOnAnimationStatus(uint8 InBit)
{
	MonsterAnimationStatus |= InBit;
}

void UMonsterStatusComponent::SetOffAnimationStatus(uint8 InBit)
{
	MonsterAnimationStatus &= ~(InBit);
}

bool UMonsterStatusComponent::GetAnimStatus(uint8 InBit) const
{
	return MonsterAnimationStatus & InBit;
}
