// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StatusComponent/StatusComponent.h"
#include "LinkStatusComponent.generated.h"

#define	LINK_BIT_WAIT			0x00000001
#define	LINK_BIT_WALK			0x00000002
#define	LINK_BIT_RUN			0x00000004
#define	LINK_BIT_CARRY			0x00000008

#define LINK_TOOl_BIT_SWORD				0x00000001
#define LINK_TOOl_BIT_SHIELD			0x00000002
#define LINK_TOOl_BIT_MIRRORSHIELD		0x00000004
#define LINK_TOOl_BIT_FLIPPER			0x00000008
#define LINK_TOOl_BIT_OCARINA			0x00000010


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
	UPROPERTY()
	uint8 LinkToolOwnStatus;
	UPROPERTY()
	uint8 LinkToolEquipStatus;

public:
	void SetOnAnimationStatus(uint8 InBit);
	void SetOffAnimationStatus(uint8 InBit);

public:
	void SetOnToolOwnStatus(uint8 InBit);
	void SetOffToolOwnStatus(uint8 InBit);

public:
	void SetOnToolEqupStatus(uint8 InBit);
	void SetOffToolEquipStatus(uint8 InBit);


public:
	UFUNCTION()
	bool GetAnimStatus(uint8 InBit) const;
	UFUNCTION()
	bool GetToolOwnStatus(uint8 InBit) const;
	UFUNCTION()
	bool GetToolEquipStatus(uint8 InBit) const;

protected:
	bool bIsCatched = false;
public:
	void SetIsCatched(bool _bIsCatched) { bIsCatched = _bIsCatched; }
	bool GetIsCatched() const { return bIsCatched; }
};
