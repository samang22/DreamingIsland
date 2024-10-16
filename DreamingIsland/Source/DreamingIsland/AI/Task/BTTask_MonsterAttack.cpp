// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Task/BTTask_MonsterAttack.h"
#include "Animation/MonsterAnimInstance.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Blueprint/AIAsyncTaskBlueprintProxy.h"

UBTTask_MonsterAttack::UBTTask_MonsterAttack()
{
	NodeName = "MonsterAttack";
	bCreateNodeInstance = true;
	bTickIntervals = true;
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_MonsterAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	BehaviorTreeComponent = &OwnerComp;
	BlackboardComponent = OwnerComp.GetBlackboardComponent();

	APawn* Pawn = AIOwner->GetPawn();
	USkeletalMeshComponent* SkeletalMeshComponent = Pawn->GetComponentByClass<USkeletalMeshComponent>();
	UMonsterAnimInstance* AnimInstance = Cast<UMonsterAnimInstance>(SkeletalMeshComponent->GetAnimInstance());
	AnimInstance->PlayAttackMontage();

	//return EBTNodeResult::InProgress;
	return EBTNodeResult::Succeeded;
}

void UBTTask_MonsterAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	// Do Nothing
}

