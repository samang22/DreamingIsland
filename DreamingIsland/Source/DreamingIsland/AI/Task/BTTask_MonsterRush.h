// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/Task/BTTask_Base.h"
#include "BTTask_MonsterRush.generated.h"

/**
 * 
 */

#define MONSTER_RUSH_DISTANCE 200.f

UCLASS()
class DREAMINGISLAND_API UBTTask_MonsterRush : public UBTTask_Base
{
	GENERATED_BODY()
public:
	UBTTask_MonsterRush();


	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;


protected:
	class UBehaviorTreeComponent* BehaviorTreeComponent = nullptr;
	class UBlackboardComponent* BlackboardComponent = nullptr;
};


