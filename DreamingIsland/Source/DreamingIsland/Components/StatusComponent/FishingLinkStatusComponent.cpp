// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/StatusComponent/FishingLinkStatusComponent.h"
#include "Misc/Utils.h"

UFishingLinkStatusComponent::UFishingLinkStatusComponent()
{
	SetOnAnimationStatus(LINK_BIT_WAIT);
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
