// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Task/Hinox/BTTask_ThrowBomb.h"
#include "Animation/MonsterAnimInstance.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Actors/Monster.h"

UBTTask_ThrowBomb::UBTTask_ThrowBomb()
{
	NodeName = "ThrowBomb";
	bCreateNodeInstance = true;
	bTickIntervals = true;
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_ThrowBomb::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	BehaviorTreeComponent = &OwnerComp;
	BlackboardComponent = OwnerComp.GetBlackboardComponent();

	AMonster* Monster = Cast<AMonster>(AIOwner->GetPawn());
	ACharacter* Character = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	if (!Character || !Monster)
	{
		return EBTNodeResult::Failed;
	}

	const float Dist = FVector::Dist(Monster->GetActorLocation(), Character->GetActorLocation());

	if (Dist < HINOX_THROW_BOMB_MIN_LENGTH
		|| Dist > HINOX_THROW_BOMB_MAX_LENGTH)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed"));

		return EBTNodeResult::Failed;
	}
	UE_LOG(LogTemp, Warning, TEXT("Succeeded"));

	if (!Monster->GetIsWeaponEquiped())
	{
		Monster->SetWeaponEquiped();
		Monster->RenderOnWeapon();
	}

	Monster->PlayMontage(MONSTER_MONTAGE::THROW);

	return EBTNodeResult::InProgress;
}

void UBTTask_ThrowBomb::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AMonster* Monster = Cast<AMonster>(AIOwner->GetPawn());
	if (Monster->IsPlayingMontage(MONSTER_MONTAGE::THROW))
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::InProgress);
		return;
	}
	else
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return;
	}
}
