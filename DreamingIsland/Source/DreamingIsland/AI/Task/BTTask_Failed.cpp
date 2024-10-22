// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Task/BTTask_Failed.h"

EBTNodeResult::Type UBTTask_Failed::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    return EBTNodeResult::Failed;
}
