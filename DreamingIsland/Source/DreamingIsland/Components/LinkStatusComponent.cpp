// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/LinkStatusComponent.h"

ULinkStatusComponent::ULinkStatusComponent()
{
	SetOnLinkAnimationStatus(LINK_BIT_WAIT);
}

void ULinkStatusComponent::SetOnLinkAnimationStatus(uint8 InBit)
{
	LinkAnimationStatus |= InBit;
}

void ULinkStatusComponent::SetOffLinkAnimationStatus(uint8 InBit)
{
	LinkAnimationStatus &= ~(InBit);
}

bool ULinkStatusComponent::GetIsWait() const
{
	return LinkAnimationStatus & LINK_BIT_WAIT;
}

bool ULinkStatusComponent::GetIsWalk() const
{
	return LinkAnimationStatus & LINK_BIT_WALK;
}

bool ULinkStatusComponent::GetIsRun() const
{
	return LinkAnimationStatus & LINK_BIT_RUN;
}

bool ULinkStatusComponent::GetIsSlash() const
{
	return LinkAnimationStatus & LINK_BIT_SLASH;
}

bool ULinkStatusComponent::GetIsSlashHold() const
{
	return LinkAnimationStatus & LINK_BIT_SLASH_HOLD;
}

bool ULinkStatusComponent::GetIsDeath() const
{
	return LinkAnimationStatus & LINK_BIT_DEATH;
}
