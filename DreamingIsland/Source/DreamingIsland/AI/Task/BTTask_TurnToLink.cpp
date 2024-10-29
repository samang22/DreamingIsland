// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Task/BTTask_TurnToLink.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Actors/Monster.h"
#include "Misc/Utils.h"

EBTNodeResult::Type UBTTask_TurnToLink::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	BehaviorTreeComponent = &OwnerComp;
	BlackboardComponent = OwnerComp.GetBlackboardComponent();

	if (!AIOwner) return EBTNodeResult::Failed;

	AMonster* Monster = Cast<AMonster>(AIOwner->GetPawn());
	ACharacter* Character = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	
	if (!Character || !Monster)
	{
		UE_LOG(LogTemp, Warning, TEXT("TurnToLink_Failed"));
		return EBTNodeResult::Failed;
	}

	FVector Dir = Character->GetActorLocation() - Monster->GetActorLocation();
	Dir.Z = 0.f;
	Dir.Normalize();
	GoalDir = Dir;

	UE_LOG(LogTemp, Warning, TEXT("TurnToLink_Success"));

	return EBTNodeResult::InProgress;
}

void UBTTask_TurnToLink::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	UE_LOG(LogTemp, Warning, TEXT("TurnToLink_Tick"));

	AMonster* Monster = Cast<AMonster>(AIOwner->GetPawn());
	const FVector MonsterForwardVector = Monster->GetActorForwardVector();
	if (IsNearlyEqualVector_My(GoalDir, MonsterForwardVector))
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}

	//const float DeltaSpeed = FMath::Clamp(DeltaSeconds * TURN_SPEED, 0.f, 1.f);
	const float DeltaSpeed = DeltaSeconds * TURN_SPEED;
	FVector NewForward;
	NewForward = FMath::Lerp(MonsterForwardVector, GoalDir, DeltaSpeed);
	Monster->SetActorRotation(NewForward.Rotation().Quaternion());

	FinishLatentTask(OwnerComp, EBTNodeResult::InProgress);
}
