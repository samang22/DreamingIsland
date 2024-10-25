// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/HinoxStatusComponent.h"

void UHinoxStatusComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	CoolTime += DeltaTime;
}

bool UHinoxStatusComponent::ThrowBomb()
{
	if (CoolTime > HINOX_THROW_BOMB_COOLTIME)
	{
		CoolTime = 0.f;
		return true;
	}

	return false;
}
