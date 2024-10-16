// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/AI/BasicMonsterAIController.h"
#include "GameFramework/Character.h"
#include "Components/StatusComponent.h"
#include "Kismet/KismetSystemLibrary.h"

void ABasicMonsterAIController::BeginPlay()
{
	Super::BeginPlay();
	if (!IsValid(PatrolPath))
	{
		checkf(false, TEXT("PatrolPath not valid"));
		return;
	}

	if (!IsValid(BrainComponent))
	{
		UBehaviorTree* BehaviorTree = LoadObject<UBehaviorTree>(nullptr, TEXT("/Script/AIModule.BehaviorTree'/Game/Blueprint/AI/BT_BasicEnemy.BT_BasicEnemy'"));
		check(BehaviorTree);
		RunBehaviorTree(BehaviorTree);
	}

	Blackboard->SetValueAsObject(TEXT("SplineComponent"), PatrolPath);
}

void ABasicMonsterAIController::OnPossess(APawn* InPawn)
{
}

void ABasicMonsterAIController::Tick(float DeltaTime)
{
}

void ABasicMonsterAIController::OnDamaged(float CurrentHP, float MaxHP)
{
}

void ABasicMonsterAIController::ResetOnDamaged()
{
}

void ABasicMonsterAIController::FindPlayerByPerception()
{
}
