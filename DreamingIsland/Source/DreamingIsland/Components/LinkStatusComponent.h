// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StatusComponent.h"
#include "LinkStatusComponent.generated.h"

#define	LINK_BIT_WAIT			0x00000001
#define	LINK_BIT_WALK			0x00000002
#define	LINK_BIT_RUN			0x00000004
#define	LINK_BIT_DEATH			0x00000008
#define	LINK_BIT_SLASH			0x00000016
#define	LINK_BIT_SLASH_HOLD		0x00000032




/**
 * 
 */
UCLASS()
class DREAMINGISLAND_API ULinkStatusComponent : public UStatusComponent
{
	GENERATED_BODY()
	
public:
	ULinkStatusComponent();

protected:
	UPROPERTY()
	uint8 LinkAnimationStatus;

protected:
	void SetOnLinkAnimationStatus(uint8 InBit);
	void SetOffLinkAnimationStatus(uint8 InBit);

public:
	UFUNCTION()
	bool GetIsWait() const;
	UFUNCTION()
	bool GetIsWalk() const;
	UFUNCTION()
	bool GetIsRun() const;
	UFUNCTION()
	bool GetIsSlash() const;
	UFUNCTION()
	bool GetIsSlashHold() const;
	UFUNCTION()
	bool GetIsDeath() const;

};
