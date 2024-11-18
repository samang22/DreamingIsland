// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Task/Hinox/BTTask_Catch.h"
#include "Animation/MonsterAnimInstance.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Actors/Monsters/Monster.h"
#include "Components/StatusComponent/MonsterStatusComponent.h"
#include "Components/StatusComponent/HinoxStatusComponent.h"
#include "Misc/Utils.h"

UBTTask_Catch::UBTTask_Catch()
{
	NodeName = "Catch";
	bCreateNodeInstance = true;
	bTickIntervals = true;
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_Catch::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	BehaviorTreeComponent = &OwnerComp;
	BlackboardComponent = OwnerComp.GetBlackboardComponent();

	AMonster* Monster = Cast<AMonster>(AIOwner->GetPawn());

	UHinoxStatusComponent* HinoxStatusComponent = Cast<UHinoxStatusComponent>(Monster->GetStatusComponent());
	if (!HinoxStatusComponent)
	{
		return EBTNodeResult::Failed;
	}
	const bool bIsHinoxRun = HinoxStatusComponent->GetIsRun();
	if (!bIsHinoxRun)
	{
		return EBTNodeResult::Failed;
	}

	HinoxStatusComponent->SetIsRun(false);

	if (!Monster->GetStatusComponent()->GetAnimStatus(MONSTER_BIT_RUSH))
	{
		return EBTNodeResult::Failed;
	}

	ACharacter* Character = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	if (!Character || !Monster)
	{
		BlackboardComponent->SetValueAsBool(TEXT("CatchTried"), false);
		return EBTNodeResult::Failed;
	}

	Monster->GetStatusComponent()->SetOffAnimationStatus(MONSTER_BIT_RUSH);






	float Distance = FVector::Dist2D(Character->GetActorLocation(), Monster->GetActorLocation());


	if (!Monster->IsPlayingMontage(MONSTER_MONTAGE::DAMAGE))
	{
		Monster->PlayMontage(MONSTER_MONTAGE::ATTACK);
		BlackboardComponent->SetValueAsBool(TEXT("CatchTried"), true);

		return EBTNodeResult::InProgress;
	}
	else
	{
		BlackboardComponent->SetValueAsBool(TEXT("CatchTried"), false);
		return EBTNodeResult::Failed;
	}
}

void UBTTask_Catch::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
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
