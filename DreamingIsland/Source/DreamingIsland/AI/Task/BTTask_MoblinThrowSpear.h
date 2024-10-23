// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/Task/BTTask_Base.h"
#include "BTTask_MoblinThrowSpear.generated.h"

/**
 * 
 */
UCLASS()
class DREAMINGISLAND_API UBTTask_MoblinThrowSpear : public UBTTask_Base
{
	GENERATED_BODY()
public:
	UBTTask_MoblinThrowSpear();


	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;


protected:
	class UBehaviorTreeComponent* BehaviorTreeComponent = nullptr;
	class UBlackboardComponent* BlackboardComponent = nullptr;
};
