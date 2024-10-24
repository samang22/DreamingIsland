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

	ACharacter* Character = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (!Character || !Monster)
	{
		return EBTNodeResult::Failed;
	}
	FVector Dir = Character->GetActorLocation() - Monster->GetActorLocation();
	Dir.Z = 0.f;
	Dir.Normalize();


	Monster->SetActorRotation(Dir.Rotation().Quaternion());
	Monster->PlayMontage(MONSTER_MONTAGE::RUSH);

	return EBTNodeResult::InProgress;
}

void UBTTask_HinoxRun::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AMonster* Monster = Cast<AMonster>(AIOwner->GetPawn());
	if (Monster->IsPlayingMontage(MONSTER_MONTAGE::RUSH))
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::InProgress);
		return;
	}
	else
	{
		if (Count < 2)
		{
			Monster->PlayMontage(MONSTER_MONTAGE::RUSH);
			FinishLatentTask(OwnerComp, EBTNodeResult::InProgress);
			++Count;
			return;
		}
		else
		{
			Count = 0;
			FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
			return;
		}
	}
}
