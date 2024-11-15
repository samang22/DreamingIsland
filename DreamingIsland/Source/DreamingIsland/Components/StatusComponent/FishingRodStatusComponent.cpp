// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/StatusComponent/FishingRodStatusComponent.h"
#include "Misc/Utils.h"

UFishingRodStatusComponent::UFishingRodStatusComponent()
{
	SetOnAnimationStatus(FISHINGROD_BIT_IDLE);
}

void UFishingRodStatusComponent::SetOnAnimationStatus(uint8 InBit)
{
	FishingRodAnimationStatus |= InBit;
}

void UFishingRodStatusComponent::SetOffAnimationStatus(uint8 InBit)
{
	FishingRodAnimationStatus &= ~(InBit);
}

bool UFishingRodStatusComponent::GetAnimStatus(uint8 InBit) const
{
	return FishingRodAnimationStatus & InBit;
}

void UFishingRodStatusComponent::SetFishingRodStatus(FISHINGROD_STATUS eStatus)
{
	eFishingRodStatus = eStatus;

	switch (eFishingRodStatus)
	{
	case FISHINGROD_STATUS::IDLE:
		SetOnAnimationStatus(FISHINGROD_BIT_IDLE);
		SetOffAnimationStatus(FISHINGROD_BIT_FIGHTING);
		SetOffAnimationStatus(FISHINGROD_BIT_FISHLOST);
		SetOffAnimationStatus(FISHINGROD_BIT_THROW_ST);
		SetOffAnimationStatus(FISHINGROD_BIT_THROW_ED);
		break;
	case FISHINGROD_STATUS::FIGHTING:
		SetOnAnimationStatus(FISHINGROD_BIT_FIGHTING);
		SetOffAnimationStatus(FISHINGROD_BIT_IDLE);
		SetOffAnimationStatus(FISHINGROD_BIT_FISHLOST);
		SetOffAnimationStatus(FISHINGROD_BIT_THROW_ST);
		SetOffAnimationStatus(FISHINGROD_BIT_THROW_ED);
		break;
	case FISHINGROD_STATUS::FISH_LOST:
		SetOnAnimationStatus(FISHINGROD_BIT_FISHLOST);
		SetOffAnimationStatus(FISHINGROD_BIT_FIGHTING);
		SetOffAnimationStatus(FISHINGROD_BIT_IDLE);
		SetOffAnimationStatus(FISHINGROD_BIT_THROW_ST);
		SetOffAnimationStatus(FISHINGROD_BIT_THROW_ED);
		break;
	case FISHINGROD_STATUS::THROW_ST:
		SetOnAnimationStatus(FISHINGROD_BIT_THROW_ST);
		SetOffAnimationStatus(FISHINGROD_BIT_FIGHTING);
		SetOffAnimationStatus(FISHINGROD_BIT_FISHLOST);
		SetOffAnimationStatus(FISHINGROD_BIT_IDLE);
		SetOffAnimationStatus(FISHINGROD_BIT_THROW_ED);
		break;
	case FISHINGROD_STATUS::THROW_ED:
		SetOnAnimationStatus(FISHINGROD_BIT_THROW_ED);
		SetOffAnimationStatus(FISHINGROD_BIT_FIGHTING);
		SetOffAnimationStatus(FISHINGROD_BIT_FISHLOST);
		SetOffAnimationStatus(FISHINGROD_BIT_THROW_ST);
		SetOffAnimationStatus(FISHINGROD_BIT_IDLE);
		break;
	case FISHINGROD_STATUS::END:
	default:
		break;

	}
}
