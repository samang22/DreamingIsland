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
