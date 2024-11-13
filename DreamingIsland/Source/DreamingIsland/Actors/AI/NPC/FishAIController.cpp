// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/AI/NPC/FishAIController.h"
#include "Components/SplineComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Actors/NPC/FishingLure.h"


void AFishAIController::BeginPlay()
{
	Super::BeginPlay();
}

void AFishAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void AFishAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FindLureByPerception();
}

void AFishAIController::SetPatrolPath(TObjectPtr<USplineComponent> NewPatrolPath)
{
	PatrolPath = NewPatrolPath;

	if (!IsValid(PatrolPath))
	{
		return;
	}

	UBehaviorTree* BehaviorTree = nullptr;
	if (!IsValid(BrainComponent))
	{
		BehaviorTree = LoadObject<UBehaviorTree>(nullptr, TEXT("/Script/AIModule.BehaviorTree'/Game/Blueprint/AI/NPC/BT_Fish.BT_Fish'"));
		check(BehaviorTree);
		RunBehaviorTree(BehaviorTree);
	}

	Blackboard->SetValueAsObject(TEXT("SplineComponent"), PatrolPath);
}

void AFishAIController::FindLureByPerception()
{
	APawn* OwningPawn = GetPawn();
	if (UAIPerceptionComponent* AIPerceptionComponent = OwningPawn->GetComponentByClass<UAIPerceptionComponent>())
	{
		TArray<AActor*> OutActors;
		AIPerceptionComponent->GetCurrentlyPerceivedActors(UAISenseConfig_Sight::StaticClass(), OutActors);

		bool bFound = false;
		for (AActor* It : OutActors)
		{
			if (AFishingLure* DetectedPlayer = Cast<AFishingLure>(It))
			{
				bFound = true;
				Blackboard->SetValueAsObject(TEXT("DetectedLure"), Cast<UObject>(DetectedPlayer));
				break;
			}
		}
		if (!bFound && Blackboard)
		{
			Blackboard->ClearValue(TEXT("DetectedLure"));
		}
	}
}
