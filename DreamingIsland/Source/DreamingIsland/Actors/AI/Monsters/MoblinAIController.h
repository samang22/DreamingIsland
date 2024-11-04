// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/AI/BaseAIController.h"

#include "MoblinAIController.generated.h"

UCLASS()
class DREAMINGISLAND_API AMoblinAIController : public ABaseAIController
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaTime) override;

protected:
	UFUNCTION()
	void OnDamaged(float CurrentHP, float MaxHP);

	UFUNCTION()
	void ResetOnDamaged();
	void FindPlayerByPerception();

public:
	void SetPatrolPath(TObjectPtr<USplineComponent> NewPatrolPath);

protected:
	bool bDamaged = false;
};
