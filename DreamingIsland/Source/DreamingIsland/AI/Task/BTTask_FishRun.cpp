// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Task/BTTask_FishRun.h"
#include "Actors/NPC/Fish.h"
#include "Misc/Utils.h"

UBTTask_FishRun::UBTTask_FishRun()
{
	NodeName = "FishRun";
	bCreateNodeInstance = true;
	bTickIntervals = true;
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_FishRun::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	BehaviorTreeComponent = &OwnerComp;
	BlackboardComponent = OwnerComp.GetBlackboardComponent();

	return EBTNodeResult::InProgress;
}

void UBTTask_FishRun::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AActor* Lure = Cast<AActor>(BlackboardComponent->GetValueAsObject(TEXT("DetectedLure")));
	AFish* Fish = Cast<AFish>(AIOwner->GetPawn());
	if (!Lure || !Fish)
	{
		FinishLatentTask(*BehaviorTreeComponent, EBTNodeResult::Failed);
		return;
	}

	FVector Direction = Fish->GetActorLocation() - Lure->GetActorLocation();
	Direction.Normalize();

	const FName FishName = Fish->GetFishName();

	float Force = 0.f;
	if (FishName == TEXT("SmallFish"))
	{
		Force = SMALLFISH_PULL_FORCE;
	}
	else if (FishName == TEXT("BigFish"))
	{
		Force = BIGFISH_PULL_FORCE;
	}
	Direction.Z = 0.0;
	Fish->AddForce(Direction * Force);
	Fish->SetDesiredDirection(Direction);

	if (FVector::Dist(Lure->GetActorLocation(), Fish->GetActorLocation()) > FISH_AISENSECONFIG_SIGHT_LOSESIGHTRADIUS)
	{
		FinishLatentTask(*BehaviorTreeComponent, EBTNodeResult::Failed);
	}
	FinishLatentTask(*BehaviorTreeComponent, EBTNodeResult::InProgress);
}
