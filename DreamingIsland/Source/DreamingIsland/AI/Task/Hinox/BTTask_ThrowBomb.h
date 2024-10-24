// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/Task/BTTask_Base.h"
#include "BTTask_ThrowBomb.generated.h"


#define HINOX_THROW_BOMB_MIN_LENGTH 200.f
#define HINOX_THROW_BOMB_MAX_LENGTH 400.f

UCLASS()
class DREAMINGISLAND_API UBTTask_ThrowBomb : public UBTTask_Base
{
	GENERATED_BODY()
public:
	UBTTask_ThrowBomb();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

protected:
	class UBehaviorTreeComponent* BehaviorTreeComponent = nullptr;
	class UBlackboardComponent* BlackboardComponent = nullptr;
};
