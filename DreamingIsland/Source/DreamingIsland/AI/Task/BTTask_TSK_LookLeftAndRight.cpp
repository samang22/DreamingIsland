// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Task/BTTask_TSK_LookLeftAndRight.h"
#include "BTTask_TSK_LookLeftAndRight.h"
#include "Animation/NPCAnimInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Actors/NPC/ToolShopKeeper.h"

UBTTask_TSK_LookLeftAndRight::UBTTask_TSK_LookLeftAndRight()
{
	NodeName = "LookLeftAndRight";
	bCreateNodeInstance = true;
	bTickIntervals = true;
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_TSK_LookLeftAndRight::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	BehaviorTreeComponent = &OwnerComp;
	BlackboardComponent = OwnerComp.GetBlackboardComponent();

	AToolShopKeeper* ToolShopKeeper = Cast<AToolShopKeeper>(AIOwner->GetPawn());
	if (!ToolShopKeeper)
	{
		return EBTNodeResult::Failed;
	}

	if (ToolShopKeeper->GetIsShootBeam())
	{
		return EBTNodeResult::Failed;
	}


	ToolShopKeeper->SetIsWatching(true);
	return EBTNodeResult::Failed;
}

void UBTTask_TSK_LookLeftAndRight::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
}
