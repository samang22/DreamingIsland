// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/AI/NPC/NPCAIController.h"
#include "GameShopOwnerAIController.generated.h"

UCLASS()
class DREAMINGISLAND_API AGameShopOwnerAIController : public ANPCAIController
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaTime) override;
};
