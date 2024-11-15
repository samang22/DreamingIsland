// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StatusComponent/StatusComponent.h"
#include "Misc/Utils.h"
#include "FishingRodStatusComponent.generated.h"

UCLASS()
class DREAMINGISLAND_API UFishingRodStatusComponent : public UStatusComponent
{
	GENERATED_BODY()
public:
	UFishingRodStatusComponent();

protected:
	UPROPERTY()
	uint8 FishingRodAnimationStatus;

public:
	void SetOnAnimationStatus(uint8 InBit);
	void SetOffAnimationStatus(uint8 InBit);

public:
	UFUNCTION()
	bool GetAnimStatus(uint8 InBit) const;

protected:
	FISHINGROD_STATUS eFishingRodStatus = FISHINGROD_STATUS::IDLE;
public:
	void SetFishingRodStatus(FISHINGROD_STATUS eStatus);
	FISHINGROD_STATUS GetFishingRodStatus() const { return eFishingRodStatus; };
};
