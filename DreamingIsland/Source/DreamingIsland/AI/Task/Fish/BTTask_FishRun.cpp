// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Task/Fish/BTTask_FishRun.h"
#include "Actors/NPC/Fish.h"
#include "Misc/Utils.h"
#include "Components/StatusComponent/FishStatusComponent.h"

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

	AFish* Fish = Cast<AFish>(AIOwner->GetPawn());
	if (!Fish)
	{
		return EBTNodeResult::Failed;
	}
	if (FISH_STATUS::FIGHTING == Fish->GetStatusComponent()->GetFishStatus())
	{
		return EBTNodeResult::Failed;
	}

	return EBTNodeResult::InProgress;
}

void UBTTask_FishRun::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	UE_LOG(LogTemp, Warning, TEXT("FishRun"));

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
	Direction.Z = 0.5;
	Fish->AddForce(Direction * Force);
	Fish->SetDesiredDirection(Direction);

	if (FVector::Dist(Lure->GetActorLocation(), Fish->GetActorLocation()) > FISH_AISENSECONFIG_SIGHT_LOSESIGHTRADIUS)
	{
		FinishLatentTask(*BehaviorTreeComponent, EBTNodeResult::Failed);
	}
	FinishLatentTask(*BehaviorTreeComponent, EBTNodeResult::InProgress);
}
