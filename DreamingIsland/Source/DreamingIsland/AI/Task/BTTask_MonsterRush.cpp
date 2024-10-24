// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Task/BTTask_MonsterRush.h"
#include "Animation/MonsterAnimInstance.h"
#include "Actors/Monster.h"

UBTTask_MonsterRush::UBTTask_MonsterRush()
{
	NodeName = "MonsterRush";
	bCreateNodeInstance = true;
	bTickIntervals = true;
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_MonsterRush::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// in this func, Failed to run next node
	// 


	BehaviorTreeComponent = &OwnerComp;
	BlackboardComponent = OwnerComp.GetBlackboardComponent();

	AMonster* Monster = Cast<AMonster>(AIOwner->GetPawn());
	AActor* PlayerActor = Cast<AActor>(BlackboardComponent->GetValueAsObject(TEXT("DetectedPlayer")));
	if (PlayerActor)
	{
		const float Distance = FVector::Dist(PlayerActor->GetActorLocation(), Monster->GetActorLocation());

		if (Distance > MONSTER_RUSH_DISTANCE)
		{
			Monster->PlayMontage(MONSTER_MONTAGE::RUSH);
			return EBTNodeResult::InProgress;
		}
	}
	return EBTNodeResult::Failed;
}

void UBTTask_MonsterRush::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AMonster* Monster = Cast<AMonster>(AIOwner->GetPawn());
	AActor* PlayerActor = Cast<AActor>(BlackboardComponent->GetValueAsObject(TEXT("DetectedPlayer")));

	if (PlayerActor)
	{
		const float Distance = FVector::Dist(PlayerActor->GetActorLocation(), Monster->GetActorLocation());
		if (Distance < MONSTER_RUSH_DISTANCE)
		{
			FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		}
		else
		{
			FinishLatentTask(OwnerComp, EBTNodeResult::InProgress);
		}
	}
	else
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}
}
