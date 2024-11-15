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

void UFishStatusComponent::SetFishStatus(FISH_STATUS eStatus)
{
	eFishStatus = eStatus;

	switch (eFishStatus)
	{
	case FISH_STATUS::IDLE:
		SetOnAnimationStatus(FISH_BIT_WAIT);
		SetOffAnimationStatus(FISH_BIT_CATCHING);
		SetOffAnimationStatus(FISH_BIT_GET);
		SetOffAnimationStatus(FISH_BIT_POKEWAIT);
		break;
	case FISH_STATUS::POKE:
		SetOnAnimationStatus(FISH_BIT_POKEWAIT);
		SetOffAnimationStatus(FISH_BIT_WAIT);
		SetOffAnimationStatus(FISH_BIT_CATCHING);
		SetOffAnimationStatus(FISH_BIT_GET);
		break;
	case FISH_STATUS::FIGHTING:
		SetOnAnimationStatus(FISH_BIT_WAIT);
		SetOffAnimationStatus(FISH_BIT_CATCHING);
		SetOffAnimationStatus(FISH_BIT_GET);
		SetOffAnimationStatus(FISH_BIT_POKEWAIT);
		break;
	case FISH_STATUS::CATCHED:
		SetOnAnimationStatus(FISH_BIT_GET);
		SetOffAnimationStatus(FISH_BIT_WAIT);
		SetOffAnimationStatus(FISH_BIT_CATCHING);
		SetOffAnimationStatus(FISH_BIT_POKEWAIT);
		break;
	case FISH_STATUS::END:
		break;
	default:
		break;
	}
}
