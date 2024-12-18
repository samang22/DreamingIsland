// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Task/Hinox/BTTask_CatchNo.h"
#include "Animation/MonsterAnimInstance.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Actors/Monsters/Hinox.h"
#include "Components/StatusComponent/HinoxStatusComponent.h"
UBTTask_CatchNo::UBTTask_CatchNo()
{
	NodeName = "CatchNo";
	bCreateNodeInstance = true;
	bTickIntervals = true;
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_CatchNo::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	BehaviorTreeComponent = &OwnerComp;
	BlackboardComponent = OwnerComp.GetBlackboardComponent();

	const bool bCatchTried = BlackboardComponent->GetValueAsBool(TEXT("CatchTried"));
	if (!bCatchTried)
	{
		return EBTNodeResult::Failed;
	}


	AHinox* Monster = Cast<AHinox>(AIOwner->GetPawn());
	UHinoxStatusComponent* HinoxStatusComponent = Cast<UHinoxStatusComponent>(Monster->GetStatusComponent());
	if (HinoxStatusComponent->GetIsCatching())
	{
		return EBTNodeResult::Failed;
	}

	BlackboardComponent->SetValueAsBool(TEXT("CatchTried"), false);

	if (!Monster->IsPlayingMontage(MONSTER_MONTAGE::DAMAGE))
	{
		Monster->PlayMontage(MONSTER_MONTAGE::CATCH_NO);
		return EBTNodeResult::InProgress;
	}
	else
	{
		return EBTNodeResult::Failed;
	}
}

void UBTTask_CatchNo::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AMonster* Monster = Cast<AMonster>(AIOwner->GetPawn());
	if (Monster->IsPlayingMontage(MONSTER_MONTAGE::CATCH_NO))
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
