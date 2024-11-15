// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/StatusComponent/FishingLinkStatusComponent.h"
#include "Misc/Utils.h"

UFishingLinkStatusComponent::UFishingLinkStatusComponent()
{
	SetOnAnimationStatus(LINK_BIT_WAIT);
	EFishingLinkStatus = FISHINGLINK_STATUS::IDLE;
}

void UFishingLinkStatusComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UFishingLinkStatusComponent::SetOnAnimationStatus(uint8 InBit)
{
	LinkAnimationStatus |= InBit;
}

void UFishingLinkStatusComponent::SetOffAnimationStatus(uint8 InBit)
{
	LinkAnimationStatus &= ~(InBit);
}

bool UFishingLinkStatusComponent::GetAnimStatus(uint8 InBit) const
{
	return LinkAnimationStatus & InBit;
}

void UFishingLinkStatusComponent::SetFishingLinkStatus(FISHINGLINK_STATUS eFlag)
{
	EFishingLinkStatus = eFlag;

	switch (EFishingLinkStatus)
	{
	case FISHINGLINK_STATUS::IDLE:
		SetOnAnimationStatus(FISHINGLINK_BIT_IDLE);
		break;
	case FISHINGLINK_STATUS::FISHING:
		SetOnAnimationStatus(FISHINGLINK_BIT_FISHING);
		break;
	case FISHINGLINK_STATUS::PULLING:
		SetOnAnimationStatus(FISHINGLINK_BIT_PULLING);
		break;
	case FISHINGLINK_STATUS::END:
	default:
		break;
	}

}
