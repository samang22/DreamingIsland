// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StatusComponent.h"
#include "NPCStatusComponent.generated.h"

#define NPC_BIT_WAIT			0x00000001
#define NPC_BIT_WALK			0x00000002

/**
 * 
 */
UCLASS()
class DREAMINGISLAND_API UNPCStatusComponent : public UStatusComponent
{
	GENERATED_BODY()
public:
	UNPCStatusComponent();

protected:
	UPROPERTY()
	uint8 NPCAnimationStatus;

public:
	void SetOnAnimationStatus(uint8 InBit);
	void SetOffAnimationStatus(uint8 InBit);

public:
	UFUNCTION()
	bool GetAnimStatus(uint8 InBit) const;
};
