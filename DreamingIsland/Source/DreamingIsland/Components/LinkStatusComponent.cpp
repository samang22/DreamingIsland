// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/LinkStatusComponent.h"

ULinkStatusComponent::ULinkStatusComponent()
{
	SetOnAnimationStatus(LINK_BIT_WAIT);
	RunCoefficient = LINK_RUN_COEFFICIENT;
}

void ULinkStatusComponent::SetOnAnimationStatus(uint8 InBit)
{
	LinkAnimationStatus |= InBit;
}

void ULinkStatusComponent::SetOffAnimationStatus(uint8 InBit)
{
	LinkAnimationStatus &= ~(InBit);
}

void ULinkStatusComponent::SetOnToolOwnStatus(uint8 InBit)
{
	LinkToolOwnStatus |= InBit;
}

void ULinkStatusComponent::SetOffToolOwnStatus(uint8 InBit)
{
	LinkToolOwnStatus &= ~(InBit);
}

void ULinkStatusComponent::SetOnToolEqupStatus(uint8 InBit)
{
	LinkToolEquipStatus |= InBit;
}

void ULinkStatusComponent::SetOffToolEquipStatus(uint8 InBit)
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