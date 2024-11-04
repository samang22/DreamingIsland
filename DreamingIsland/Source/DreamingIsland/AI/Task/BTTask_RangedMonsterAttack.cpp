// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/Task/BTTask_RangedMonsterAttack.h"
#include "Animation/MonsterAnimInstance.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Actors/Monsters/Monster.h"

UBTTask_RangedMonsterAttack::UBTTask_RangedMonsterAttack()
{
	NodeName = "RangedMonsterAttack";
	bCreateNodeInstance = true;
	bTickIntervals = true;
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_RangedMonsterAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//BehaviorTreeComponent = &OwnerComp;
	//BlackboardComponent = OwnerComp.GetBlackboardComponent();

	//AMonster* Monster = Cast<AMonster>(AIOwner->GetPawn());

	//// Rotate to Link
	//ACharacter* Character = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	//if (!Character || !Monster)
	//{
	//	return EBTNodeResult::Failed;
	//}

	//FVector Dir = Character->GetActorLocation() - Monster->GetActorLocation();
	//Dir.Z = 0.f;
	//Dir.Normalize();

	//if (!Monster->IsPlayingMontage(MONSTER_MONTAGE::DAMAGE))
	//{
	//	Monster->SetActorRotation(Dir.Rotation().Quaternion());
	//	Monster->PlayMontage(MONSTER_MONTAGE::ATTACK);
	//}
	//return EBTNodeResult::InProgress;

	BehaviorTreeComponent = &OwnerComp;
	BlackboardComponent = OwnerComp.GetBlackboardComponent();

	AMonster* Monster = Cast<AMonster>(AIOwner->GetPawn());

	ACharacter* Character = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (!Character || !Monster)
	{
		return EBTNodeResult::Failed;
	}

	FVector Dir = Character->GetActorLocation() - Monster->GetActorLocation();
	Dir.Z = 0.f;
	Dir.Normalize();

	if (!Monster->IsPlayingMontage(MONSTER_MONTAGE::DAMAGE))
	{
		Monster->SetActorRotation(Dir.Rotation().Quaternion());
		Monster->PlayMontage(MONSTER_MONTAGE::ATTACK);
	}

	return EBTNodeResult::InProgress;
}

void UBTTask_RangedMonsterAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

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
