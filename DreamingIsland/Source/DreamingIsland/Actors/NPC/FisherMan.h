// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/NPC/NPC.h"
#include "FisherMan.generated.h"

UCLASS()
class DREAMINGISLAND_API AFisherMan : public ANPC
{
	GENERATED_BODY()
public:
	AFisherMan(const FObjectInitializer& ObjectInitializer);
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
};
