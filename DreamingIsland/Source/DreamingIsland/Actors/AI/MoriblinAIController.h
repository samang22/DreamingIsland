// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MoriblinAIController.generated.h"

class UStatusComponent;
class USplineComponent;
UCLASS()
class DREAMINGISLAND_API AMoriblinAIController : public AAIController
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
	void SetPatrolPath(TObjectPtr<USplineComponent> NewPatrolPath) { PatrolPath = NewPatrolPath; }

protected:
	UPROPERTY()
	TObjectPtr<USplineComponent> PatrolPath;

protected:
	bool bDamaged = false;

	UPROPERTY()
	UStatusComponent* StatusComponentRef;

};
