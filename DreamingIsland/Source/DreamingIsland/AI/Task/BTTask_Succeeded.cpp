// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Task/BTTask_Succeeded.h"

EBTNodeResult::Type UBTTask_Succeeded::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return EBTNodeResult::Succeeded;
}
