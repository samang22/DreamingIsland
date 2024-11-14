// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Task/BTTask_MoveToLure.h"
#include "Actors/NPC/Fish.h"
#include "Misc/Utils.h"


UBTTask_MoveToLure::UBTTask_MoveToLure()
{
	NodeName = "MoveToLure";
	bCreateNodeInstance = true;
	bTickIntervals = true;
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_MoveToLure::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	BehaviorTreeComponent = &OwnerComp;
	BlackboardComponent = OwnerComp.GetBlackboardComponent();

	return EBTNodeResult::InProgress;
}

void UBTTask_MoveToLure::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AActor* Lure = Cast<AActor>(BlackboardComponent->GetValueAsObject(TEXT("DetectedLure")));
	AFish* Fish = Cast<AFish>(AIOwner->GetPawn());

	if (!Lure || !Fish)
	{
		FinishLatentTask(*BehaviorTreeComponent, EBTNodeResult::Failed);
		return;
	}

	FVector Direction = FVector::ZeroVector;
	if (Lure)
	{
		Direction = Lure->GetActorLocation() - AIOwner->GetPawn()->GetActorLocation();
		Direction.Normalize();
	}


	if (FVector::Dist(Fish->GetActorLocation(), Lure->GetActorLocation()) < FISH_POKE_DISTANCE)
	{
		FinishLatentTask(*BehaviorTreeComponent, EBTNodeResult::Failed);
		return;
	}

	float Force = 0.f;
	const FName FishName = Fish->GetFishName();
	if (FishName == TEXT("SmallFish"))
	{
		Force = SMALLFISH_MOVE_FORCE;
	}
	else if (FishName == TEXT("BigFish"))
	{
		Force = BIGFISH_MOVE_FORCE;
	}
	// to prevent fish rotate or vertial moveto far
	Fish->AddForce(Direction * Force);
	Direction.Z = 0;
	Fish->SetDesiredDirection(Direction);

	FinishLatentTask(*BehaviorTreeComponent, EBTNodeResult::InProgress);
}

