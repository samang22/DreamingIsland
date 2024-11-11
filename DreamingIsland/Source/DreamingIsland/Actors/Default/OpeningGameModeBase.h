// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "OpeningGameModeBase.generated.h"

UCLASS()
class DREAMINGISLAND_API AOpeningGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	AOpeningGameModeBase();
	virtual void StartPlay();
};
