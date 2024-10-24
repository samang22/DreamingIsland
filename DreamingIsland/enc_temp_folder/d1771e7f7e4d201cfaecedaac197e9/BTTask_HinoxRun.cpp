// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Task/Hinox/BTTask_HinoxRun.h"
#include "Animation/MonsterAnimInstance.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Actors/Monster.h"

UBTTask_HinoxRun::UBTTask_HinoxRun()
{
	NodeName = "HinoxRun";
	bCreateNodeInstance = true;
	bTickIntervals = true;
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_HinoxRun::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	BehaviorTreeComponent = &OwnerComp;
	BlackboardComponent = OwnerComp.GetBlackboardComponent();

	AMonster* Monster = Cast<AMonster>(AIOwner->GetPawn());
	AActor* PlayerActor = Cast<AActor>(BlackboardComponent->GetValueAsObject(TEXT("DetectedPlayer")));
	if (PlayerActor)
	{
		const float Distance = FVector::Dist(PlayerActor->GetActorLocation(), Monster->GetActorLocation());

		if (Distance > HINOX_LINK_RUSH_LENGTH)
		{
			Monster->PlayMontage(MONSTER_MONTAGE::RUSH, true);
			return EBTNodeResult::InProgress;
		}
	}

	return EBTNodeResult::Failed;
}

void UBTTask_HinoxRun::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AMonster* Monster = Cast<AMonster>(AIOwner->GetPawn());
	AActor* PlayerActor = Cast<AActor>(BlackboardComponent->GetValueAsObject(TEXT("DetectedPlayer")));

	if (PlayerActor)
	{
		const float Distance = FVector::Dist(PlayerActor->GetActorLocation(), Monster->GetActorLocation());
		// if Hinox is close enough
		if (Distance < HINOX_LINK_RUSH_LENGTH)
		{
			FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		}
		else
		{
			FinishLatentTask(OwnerComp, EBTNodeResult::InProgress);
		}
	}
	// if link is far away
	else
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}
}
