// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Task/Hinox/BTTask_ThrowBomb.h"
#include "Animation/MonsterAnimInstance.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Actors/Monsters/Hinox.h"
#include "Components/HinoxStatusComponent.h"

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

	AHinox* Monster = Cast<AHinox>(AIOwner->GetPawn());
	ACharacter* Character = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	if (!Character || !Monster)
	{
		return EBTNodeResult::Failed;
	}

	UHinoxStatusComponent* HinoxStatusComponent = Cast<UHinoxStatusComponent>(Monster->GetStatusComponent());

	bool bCanThrowBomb = false;
	if (HinoxStatusComponent)
	{
		bCanThrowBomb = HinoxStatusComponent->ThrowBomb();
	}

	if (!bCanThrowBomb)
	{
		UE_LOG(LogTemp, Warning, TEXT("InThrowBomb Failed CoolTime"));
		return EBTNodeResult::Failed;
	}

	const float Dist = FVector::Dist(Monster->GetActorLocation(), Character->GetActorLocation());


	if (Dist > HINOX_THROW_BOMB_MIN_LENGTH)
	{
		UE_LOG(LogTemp, Warning, TEXT("InThrowBomb Failed : %f"), Dist);

		return EBTNodeResult::Failed;
	}
	UE_LOG(LogTemp, Warning, TEXT("InThrowBomb Succeeded %f"), Dist);

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
