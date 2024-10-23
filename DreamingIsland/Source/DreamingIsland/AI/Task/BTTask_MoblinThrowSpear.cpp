// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Task/BTTask_MoblinThrowSpear.h"
#include "Animation/MonsterAnimInstance.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Actors/Monster.h"

UBTTask_MoblinThrowSpear::UBTTask_MoblinThrowSpear()
{
	NodeName = "MoblinThrowSpear";
	bCreateNodeInstance = true;
	bTickIntervals = true;
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_MoblinThrowSpear::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	BehaviorTreeComponent = &OwnerComp;
	BlackboardComponent = OwnerComp.GetBlackboardComponent();

	AMonster* Monster = Cast<AMonster>(AIOwner->GetPawn());

	if (!Monster->GetIsWeaponEquiped())
	{
		return EBTNodeResult::Failed;
	}

	ACharacter* Character = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (!Character || !Monster)
	{
		return EBTNodeResult::Failed;
	}

	FVector Dir = Character->GetActorLocation() - Monster->GetActorLocation();
	Dir.Normalize();

	Monster->SetActorRotation(Dir.Rotation().Quaternion());
	Monster->PlayMontage(MONSTER_MONTAGE::ATTACK);
	Monster->RenderOffWeapon();
	Monster->SetWeaponUnEquiped();
	return EBTNodeResult::InProgress;
}

void UBTTask_MoblinThrowSpear::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AMonster* Monster = Cast<AMonster>(AIOwner->GetPawn());
	if (Monster->IsPlayingMontage(MONSTER_MONTAGE::ATTACK))
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
