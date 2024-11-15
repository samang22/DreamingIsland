// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StatusComponent/StatusComponent.h"
#include "Misc/Utils.h"
#include "FishingLinkStatusComponent.generated.h"



UCLASS()
class DREAMINGISLAND_API UFishingLinkStatusComponent : public UStatusComponent
{
	GENERATED_BODY()
public:
	UFishingLinkStatusComponent();
public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	UPROPERTY()
	uint8 LinkAnimationStatus;

public:
	void SetOnAnimationStatus(uint8 InBit);
	void SetOffAnimationStatus(uint8 InBit);
public:
	UFUNCTION()
	bool GetAnimStatus(uint8 InBit) const;

protected:
	FISHINGLINK_STATUS EFishingLinkStatus = FISHINGLINK_STATUS::IDLE;
public:
	void SetFishingLinkStatus(FISHINGLINK_STATUS eFlag);
	FISHINGLINK_STATUS GetFishingLinkStatus() const { return EFishingLinkStatus; }
};
