// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/Task/BTTask_Base.h"
#include "BTTask_Fish_PathTrace.generated.h"

/**
 * 
 */
UCLASS()
class DREAMINGISLAND_API UBTTask_Fish_PathTrace : public UBTTask_Base
{
	GENERATED_BODY()
public:
	UBTTask_Fish_PathTrace();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	void MoveToSplinePoint(const FVector& TargetLocation);


protected:
	class UBehaviorTreeComponent* BehaviorTreeComponent = nullptr;
	class UBlackboardComponent* BlackboardComponent = nullptr;
	class USplineComponent* SplineComponent = nullptr;
	int32 CurrentPatrolIndex = 0;
	int32 SplinePoints = 0;
};
