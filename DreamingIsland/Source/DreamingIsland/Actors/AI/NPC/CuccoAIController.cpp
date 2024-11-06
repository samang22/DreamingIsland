// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/AI/NPC/CuccoAIController.h"
#include "Components/SplineComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Decorators/BTDecorator_IsAtLocation.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"


void ACuccoAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ACuccoAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void ACuccoAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FindPlayerByPerception();
}

void ACuccoAIController::SetPatrolPath(TObjectPtr<USplineComponent> NewPatrolPath)
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
		BehaviorTree = LoadObject<UBehaviorTree>(nullptr, TEXT("/Script/AIModule.BehaviorTree'/Game/Blueprint/AI/NPC/BT_Cucco.BT_Cucco'"));
		check(BehaviorTree);
		RunBehaviorTree(BehaviorTree);
	}

	Blackboard->SetValueAsObject(TEXT("SplineComponent"), PatrolPath);
}

void ACuccoAIController::FindPlayerByPerception()
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
