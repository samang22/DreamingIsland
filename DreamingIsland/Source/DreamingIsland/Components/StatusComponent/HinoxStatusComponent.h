// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StatusComponent/MonsterStatusComponent.h"
#include "HinoxStatusComponent.generated.h"

#define HINOX_THROW_BOMB_COOLTIME 3.f

UCLASS()
class DREAMINGISLAND_API UHinoxStatusComponent : public UMonsterStatusComponent
{
	GENERATED_BODY()

protected:
	float CoolTime;
public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	bool ThrowBomb();


protected:
	bool bIsRun = false;
public:
	void SetIsRun(bool _bIsRun) { bIsRun = _bIsRun; }
	bool GetIsRun() const { return bIsRun; };

protected:
	bool bIsCatching = false;
public:
	void SetIsCatching(bool _bIsCatching) { bIsCatching = _bIsCatching; }
	bool GetIsCatching() const { return bIsCatching; };
};
