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

void ULinkStatusComponent::SetOnLinkToolOwnStatus(uint8 InBit)
{
	LinkToolOwnStatus |= InBit;
}

void ULinkStatusComponent::SetOffLinkToolOwnStatus(uint8 InBit)
{
	LinkToolOwnStatus &= ~(InBit);
}

void ULinkStatusComponent::SetOnLinkToolEqupStatus(uint8 InBit)
{
	LinkToolEquipStatus |= InBit;
}

void ULinkStatusComponent::SetOffLinkToolEquipStatus(uint8 InBit)
{
	LinkToolEquipStatus &= ~(InBit);
}

bool ULinkStatusComponent::GetAnimStatus(uint8 InBit) const
{
	return LinkAnimationStatus & InBit;
}

bool ULinkStatusComponent::GetToolOwnStatus(uint8 InBit) const
{
	return LinkToolOwnStatus & InBit;
}

bool ULinkStatusComponent::GetToolEquipStatus(uint8 InBit) const
{
	return LinkToolEquipStatus & InBit;
}