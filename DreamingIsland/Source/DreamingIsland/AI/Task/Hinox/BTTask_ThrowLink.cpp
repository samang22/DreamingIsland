// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Task/Hinox/BTTask_ThrowLink.h"
#include "Animation/MonsterAnimInstance.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Actors/Monster.h"

UBTTask_ThrowLink::UBTTask_ThrowLink()
{
	NodeName = "ThrowLink";
	bCreateNodeInstance = true;
	bTickIntervals = true;
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_ThrowLink::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	BehaviorTreeComponent = &OwnerComp;
	BlackboardComponent = OwnerComp.GetBlackboardComponent();

	BlackboardComponent->SetValueAsBool(TEXT("CatchTried"), false);

	AMonster* Monster = Cast<AMonster>(AIOwner->GetPawn());

	Monster->PlayMontage(MONSTER_MONTAGE::THROW);



	return EBTNodeResult::InProgress;
}

void UBTTask_ThrowLink::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AMonster* Monster = Cast<AMonster>(AIOwner->GetPawn());
	if (Monster->IsPlayingMontage(MONSTER_MONTAGE::THROW))
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
