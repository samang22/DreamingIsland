// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TitleGameModeBase.generated.h"

UCLASS()
class DREAMINGISLAND_API ATitleGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATitleGameModeBase();
	virtual void StartPlay();
};
