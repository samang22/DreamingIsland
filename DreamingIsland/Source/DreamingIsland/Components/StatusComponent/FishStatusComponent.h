// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StatusComponent/StatusComponent.h"
#include "FishStatusComponent.generated.h"

/**
 * 
 */
UCLASS()
class DREAMINGISLAND_API UFishStatusComponent : public UStatusComponent
{
	GENERATED_BODY()
public:
	UFishStatusComponent();

protected:
	UPROPERTY()
	uint8 FishAnimationStatus;

public:
	void SetOnAnimationStatus(uint8 InBit);
	void SetOffAnimationStatus(uint8 InBit);

public:
	UFUNCTION()
	bool GetAnimStatus(uint8 InBit) const;
};
