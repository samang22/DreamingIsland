// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StatusComponent.h"
#include "MonsterStatusComponent.generated.h"

#define MONSTER_BIT_WAIT			0x00000001
#define MONSTER_BIT_WALK			0x00000002
#define MONSTER_BIT_RUN				0x00000004
#define MONSTER_BIT_RUSH			0x00000008



UCLASS()
class DREAMINGISLAND_API UMonsterStatusComponent : public UStatusComponent
{
	GENERATED_BODY()
	
public:
	UMonsterStatusComponent();

protected:
	UPROPERTY()
	uint8 MonsterAnimationStatus;

public:
	void SetOnAnimationStatus(uint8 InBit);
	void SetOffAnimationStatus(uint8 InBit);

public:
	UFUNCTION()
	bool GetAnimStatus(uint8 InBit) const;
};
