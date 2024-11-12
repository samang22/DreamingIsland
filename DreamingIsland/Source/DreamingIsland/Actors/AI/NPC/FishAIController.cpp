// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/AI/NPC/FishAIController.h"
#include "Components/SplineComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "GameFramework/Character.h"

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
	FindPlayerByPerception();
}

void AFishAIController::SetPatrolPath(TObjectPtr<USplineComponent> NewPatrolPath)
{
	PatrolPath = NewPatrolPath;

	if (!IsValid(PatrolPath))
	{
		//checkf(false, TEXT("PatrolPath not valid"));
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

void AFishAIController::FindPlayerByPerception()
{
	APawn* OwningPawn = GetPawn();
	if (UAIPerceptionComponent* AIPerceptionComponent = OwningPawn->GetComponentByClass<UAIPerceptionComponent>())
	{
		TArray<AActor*> OutActors;
		AIPerceptionComponent->GetCurrentlyPerceivedActors(UAISenseConfig_Sight::StaticClass(), OutActors);

		bool bFound = false;
		for (AActor* It : OutActors)
		{
			if (ACharacter* DetectedPlayer = Cast<ACharacter>(It))
			{
				bFound = true;
				Blackboard->SetValueAsObject(TEXT("DetectedPlayer"), Cast<UObject>(DetectedPlayer));
				break;
			}
		}
		if (!bFound)
		{
			Blackboard->ClearValue(TEXT("DetectedPlayer"));
		}
	}
}
