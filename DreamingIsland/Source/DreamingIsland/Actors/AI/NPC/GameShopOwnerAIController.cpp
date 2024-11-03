// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/AI/NPC/GameShopOwnerAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

void AGameShopOwnerAIController::BeginPlay()
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

void AGameShopOwnerAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void AGameShopOwnerAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
