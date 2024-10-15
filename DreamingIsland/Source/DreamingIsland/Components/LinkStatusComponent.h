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
#define	LINK_BIT_SLASHHOLD		0x00000032

#define LINK_BIT_SWORD			0x00000001
#define LINK_BIT_SHIELD			0x00000002
#define LINK_BIT_MIRRORSHIELD	0x00000004
#define LINK_BIT_FLIPPER		0x00000008
#define LINK_BIT_OCARINA		0x00000016


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


protected:
	void SetOnLinkAnimationStatus(uint8 InBit);
	void SetOffLinkAnimationStatus(uint8 InBit);

protected:
	void SetOnLinkToolOwnStatus(uint8 InBit);
	void SetOffLinkToolOwnStatus(uint8 InBit);

protected:
	void SetOnLinkToolEqupStatus(uint8 InBit);
	void SetOffLinkToolEquipStatus(uint8 InBit);


public:
	UFUNCTION()
	bool GetAnimStatus(uint8 InBit) const;
	UFUNCTION()
	bool GetToolOwnStatus(uint8 InBit) const;
	UFUNCTION()
	bool GetToolEquipStatus(uint8 InBit) const;

};
