// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/NPC/NPC.h"
#include "SmallFish.generated.h"

UCLASS()
class DREAMINGISLAND_API ASmallFish : public ANPC
{
	GENERATED_BODY()
public:
	ASmallFish(const FObjectInitializer& ObjectInitializer);
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
};
