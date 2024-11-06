// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/StatusComponent/NPCStatusComponent.h"
#include "Misc/Utils.h"

UNPCStatusComponent::UNPCStatusComponent()
{
	SetOnAnimationStatus(NPC_BIT_WAIT);
}

void UNPCStatusComponent::SetOnAnimationStatus(uint8 InBit)
{
	NPCAnimationStatus |= InBit;
}

void UNPCStatusComponent::SetOffAnimationStatus(uint8 InBit)
{
	NPCAnimationStatus &= ~(InBit);
}

bool UNPCStatusComponent::GetAnimStatus(uint8 InBit) const
{
	return NPCAnimationStatus & InBit;
}
