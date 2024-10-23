// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Task/BTTask_FindWeapon.h"
#include "Animation/MonsterAnimInstance.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Actors/Monster.h"

UBTTask_FindWeapon::UBTTask_FindWeapon()
{
	NodeName = "FindWeapon";
	bCreateNodeInstance = true;
	bTickIntervals = true;
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_FindWeapon::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	BehaviorTreeComponent = &OwnerComp;
	BlackboardComponent = OwnerComp.GetBlackboardComponent();

	AMonster* Monster = Cast<AMonster>(AIOwner->GetPawn());

	if (Monster->GetIsWeaponEquiped())
	{
		return EBTNodeResult::Failed;
	}


	Monster->PlayMontage(MONSTER_MONTAGE::FIND);
	Monster->RenderOnWeapon();
	Monster->SetWeaponEquiped();
	return EBTNodeResult::InProgress;
}

void UBTTask_FindWeapon::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AMonster* Monster = Cast<AMonster>(AIOwner->GetPawn());
	if (Monster->IsPlayingMontage(MONSTER_MONTAGE::FIND))
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
