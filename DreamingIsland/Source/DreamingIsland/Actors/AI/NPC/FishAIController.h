// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/AI/BaseAIController.h"
#include "FishAIController.generated.h"

class USplineComponent;
UCLASS()
class DREAMINGISLAND_API AFishAIController : public ABaseAIController
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaTime) override;

public:
	virtual void SetPatrolPath(TObjectPtr<USplineComponent> NewPatrolPath);
protected:
	void FindLureByPerception();
};
