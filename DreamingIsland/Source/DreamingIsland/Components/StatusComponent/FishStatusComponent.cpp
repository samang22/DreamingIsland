// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/StatusComponent/FishStatusComponent.h"
#include "Misc/Utils.h"

UFishStatusComponent::UFishStatusComponent()
{
	SetOnAnimationStatus(FISH_BIT_WAIT);
}

void UFishStatusComponent::SetOnAnimationStatus(uint8 InBit)
{
	FishAnimationStatus |= InBit;
}

void UFishStatusComponent::SetOffAnimationStatus(uint8 InBit)
{
	FishAnimationStatus &= ~(InBit);
}

bool UFishStatusComponent::GetAnimStatus(uint8 InBit) const
{
	return FishAnimationStatus & InBit;
}
