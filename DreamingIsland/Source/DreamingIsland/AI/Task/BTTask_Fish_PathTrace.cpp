// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Task/BTTask_Fish_PathTrace.h"
#include "Components/SplineComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Blueprint/AIAsyncTaskBlueprintProxy.h"
#include "Actors/NPC/Fish.h"


UBTTask_Fish_PathTrace::UBTTask_Fish_PathTrace()
{
	NodeName = "Fish_PathTrace";
	bCreateNodeInstance = true;
	bTickIntervals = true;
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_Fish_PathTrace::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	BehaviorTreeComponent = &OwnerComp;
	BlackboardComponent = OwnerComp.GetBlackboardComponent();
	SplineComponent = Cast<USplineComponent>(BlackboardComponent->GetValueAsObject(TEXT("SplineComponent")));
	check(SplineComponent);

	if (SplineComponent)
	{
		SplinePoints = SplineComponent->GetNumberOfSplinePoints();
		CurrentPatrolIndex = BlackboardComponent->GetValueAsInt(TEXT("PatrolIndex"));
	}

	const FVector TargetLocation = SplineComponent->GetLocationAtSplinePoint(CurrentPatrolIndex, ESplineCoordinateSpace::World);

	if (AFish* Fish = Cast<AFish>(AIOwner->GetPawn()))
	{
		MoveToSplinePoint(TargetLocation);
	}
	else
	{
		return EBTNodeResult::Failed;
	}

	return EBTNodeResult::InProgress;
}

void UBTTask_Fish_PathTrace::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	UObject* DetectedLure = BlackboardComponent->GetValueAsObject(TEXT("DetectedLure"));
	if (IsValid(DetectedLure))
	{
		AIOwner->StopMovement();
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}

	const FVector TargetLocation = SplineComponent->GetLocationAtSplinePoint(CurrentPatrolIndex, ESplineCoordinateSpace::World);
	const FVector ActorLocation = AIOwner->GetPawn()->GetActorLocation();

	if (FVector::Dist(TargetLocation, ActorLocation) < 10.f)
	{
		CurrentPatrolIndex = ++CurrentPatrolIndex % SplinePoints;
		BlackboardComponent->SetValueAsInt(TEXT("PatrolIndex"), CurrentPatrolIndex);
	}
	else
	{
		MoveToSplinePoint(TargetLocation);
	}

	FinishLatentTask(*BehaviorTreeComponent, EBTNodeResult::InProgress);
}

void UBTTask_Fish_PathTrace::MoveToSplinePoint(const FVector& TargetLocation)
{
	if (AIOwner)
	{
		if (AFish* Fish = Cast<AFish>(AIOwner->GetPawn()))
		{                                             
			FVector Direction = (TargetLocation - Fish->GetActorLocation());
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
			Direction.Z *= 0.1f;
			Fish->AddForce(Direction * Force);
			Direction.Z = 0;
			Fish->SetDesiredDirection(Direction);
		}
	}
}