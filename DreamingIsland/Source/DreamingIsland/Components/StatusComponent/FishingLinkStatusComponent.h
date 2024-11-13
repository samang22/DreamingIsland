// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StatusComponent/StatusComponent.h"
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
	bool bIsFishing = false;
public:
	void SetIsFishing(bool bFlag) { bIsFishing = bFlag; }
	bool GetIsFishing() { return bIsFishing; }
};
