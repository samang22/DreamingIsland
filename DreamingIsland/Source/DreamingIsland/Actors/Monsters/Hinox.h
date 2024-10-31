// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Monsters/Monster.h"
#include "Hinox.generated.h"

/**
 * 
 */
UCLASS()
class DREAMINGISLAND_API AHinox : public AMonster
{
	GENERATED_BODY()
public:
	AHinox(const FObjectInitializer& ObjectInitializer);
protected:
	virtual void BeginPlay() override;


};
