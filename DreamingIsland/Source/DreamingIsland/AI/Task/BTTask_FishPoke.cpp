// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Task/BTTask_FishPoke.h"
#include "Misc/Utils.h"
#include "Actors/NPC/Fish.h"

UBTTask_FishPoke::UBTTask_FishPoke()
{
	NodeName = "FishPoke";
	bCreateNodeInstance = true;
	bTickIntervals = true;
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_FishPoke::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	BehaviorTreeComponent = &OwnerComp;
	BlackboardComponent = OwnerComp.GetBlackboardComponent();

	AFish* Fish = Cast<AFish>(AIOwner->GetPawn());
	if (!Fish) return EBTNodeResult::Failed; 
	Fish->SetPhysicsLinearVelocity(FVector::ZeroVector);

	Fish->PlayMontage(FISH_MONTAGE::POKE);

	return EBTNodeResult::InProgress;
}

void UBTTask_FishPoke::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AActor* Lure = Cast<AActor>(BlackboardComponent->GetValueAsObject(TEXT("DetectedLure")));
	AFish* Fish = Cast<AFish>(AIOwner->GetPawn());

	if (!Lure || !Fish)
	{
		FinishLatentTask(*BehaviorTreeComponent, EBTNodeResult::Failed);
		return;
	}

	FVector Direction = (Lure->GetActorLocation() - Fish->GetActorLocation());
	Direction.Normalize();
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
	Fish->AddForce(Direction * Force * 0.1f);
	Direction.Z = 0;
	Fish->SetDesiredDirection(Direction);


	if (Lure->GetVelocity().Size() > LURE_VELOCITY_LIMIT)
	{
		FinishLatentTask(*BehaviorTreeComponent, EBTNodeResult::Failed);
		return;
	}
	else
	{
		if (!Fish->IsPlayingMontage(FISH_MONTAGE::POKE))
		{
			Fish->PlayMontage(FISH_MONTAGE::POKE);
		}
	}

	FinishLatentTask(*BehaviorTreeComponent, EBTNodeResult::InProgress);
}
