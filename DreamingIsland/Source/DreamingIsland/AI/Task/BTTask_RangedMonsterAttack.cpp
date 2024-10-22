// Fill out your copyright notice in the Description page of Project Settings.

#include "Animation/MonsterAnimInstance.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "AI/Task/BTTask_RangedMonsterAttack.h"
#include "Actors/Monster.h"

FRotator GetRotationFromAToB(const FVector& A, const FVector& B)
{
	// A와 B의 정규화된 벡터 구하기
	FVector DirectionA = A.GetSafeNormal();
	FVector DirectionB = B.GetSafeNormal();

	// A에서 B로 향하는 회전 벡터 구하기
	FVector CrossProduct = FVector::CrossProduct(DirectionA, DirectionB);
	float DotProduct = FVector::DotProduct(DirectionA, DirectionB);

	// 각도 계산 (라디안 단위)
	float Angle = FMath::Acos(DotProduct);

	// 회전축과 각도로 회전 생성
	FQuat RotationQuat = FQuat(CrossProduct, Angle);
	FRotator Rotation = RotationQuat.Rotator();

	return Rotation;
}

UBTTask_RangedMonsterAttack::UBTTask_RangedMonsterAttack()
{
	NodeName = "RangedMonsterAttack";
	bCreateNodeInstance = true;
	bTickIntervals = true;
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_RangedMonsterAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	BehaviorTreeComponent = &OwnerComp;
	BlackboardComponent = OwnerComp.GetBlackboardComponent();

	AMonster* Monster = Cast<AMonster>(AIOwner->GetPawn());

	// Rotate to Link
	ACharacter* Character = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (!Character || !Monster)
	{
		return EBTNodeResult::Failed;
	}
	//const FVector LinkVector = Character->GetActorLocation();
	//const FVector MonsterVector = Monster->GetActorLocation();
	//FVector DirVector = FVector(LinkVector - MonsterVector);
	//DirVector.Normalize();
	//const FRotator ToPlayerRotator = GetRotationFromAToB(Monster->GetActorForwardVector(), DirVector);
	//Monster->SetActorRotation(ToPlayerRotator);
	Monster->PlayAttackMontage();
	return EBTNodeResult::Succeeded;
}

void UBTTask_RangedMonsterAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	AMonster* Monster = Cast<AMonster>(AIOwner->GetPawn());
	if (Monster->IsPlayingDamageMontage())
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return;
	}
	if (!Monster->IsPlayingAttackMontage())
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}
}
