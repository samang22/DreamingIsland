// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/AI/NPC/ToolShopKeeperAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

void AToolShopKeeperAIController::BeginPlay()
{
	Super::BeginPlay();

	UBehaviorTree* BehaviorTree = nullptr;
	if (!IsValid(BrainComponent))
	{
		BehaviorTree = LoadObject<UBehaviorTree>(nullptr, TEXT("/Script/AIModule.BehaviorTree'/Game/Blueprint/AI/NPC/BT_ToolShopKeeper.BT_ToolShopKeeper'"));
		check(BehaviorTree);
		RunBehaviorTree(BehaviorTree);
	}
}

void AToolShopKeeperAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void AToolShopKeeperAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
