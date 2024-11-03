// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelStreamingDynamic.h"
#include "MyLevelStreamingDynamic.generated.h"

/**
 * 
 */
UCLASS()
class DREAMINGISLAND_API UMyLevelStreamingDynamic : public ULevelStreamingDynamic
{
	GENERATED_BODY()
public:
	static ULevelStreamingDynamic* LoadLevelInstance(const FLoadLevelInstanceParams& Params, bool& bOutSuccess);

};
