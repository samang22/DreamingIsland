// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Task/Hinox/BTTask_Laugh.h"
#include "Animation/MonsterAnimInstance.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Actors/Monsters/Monster.h"

UBTTask_Laugh::UBTTask_Laugh()
{
	NodeName = "Laugh";
	bCreateNodeInstance = true;
	bTickIntervals = true;
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_Laugh::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	BehaviorTreeComponent = &OwnerComp;
	BlackboardComponent = OwnerComp.GetBlackboardComponent();

	AMonster* Monster = Cast<AMonster>(AIOwner->GetPawn());

	Monster->PlayMontage(MONSTER_MONTAGE::LAUGH);

	return EBTNodeResult::InProgress;
}

void UBTTask_Laugh::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AMonster* Monster = Cast<AMonster>(AIOwner->GetPawn());
	if (Monster->IsPlayingMontage(MONSTER_MONTAGE::LAUGH))
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::InProgress);
		return;
	}
	else
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}
}
