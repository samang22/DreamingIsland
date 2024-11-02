// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LinkData.generated.h"
/**
 * 
 */
USTRUCT()
struct DREAMINGISLAND_API FLinkData
{
	GENERATED_BODY()
public:
	uint8 LinkToolEquipStatus;
	int Rupee;
	int Bomb;
	int Arrow;
};
