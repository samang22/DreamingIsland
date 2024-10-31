// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/AI/NPC/NPCAIController.h"
#include "Actors/NPC/NPC.h"
#include "GameFramework/Character.h"
#include "Components/StatusComponent/StatusComponent.h"
#include "Components/SplineComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Decorators/BTDecorator_IsAtLocation.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Data/NPCTableRow.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

void ANPCAIController::BeginPlay()
{
	Super::BeginPlay();

	if (PatrolPath)
	{
		Blackboard->SetValueAsObject(TEXT("SplineComponent"), PatrolPath);
	}
}

void ANPCAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void ANPCAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!Blackboard) return;

	APawn* OwningPawn = GetPawn();

	// Montage가 Play 중이라면 BT 내부에서 AI 진행을 멈춘다
	const bool bMontagePlaying = OwningPawn->GetComponentByClass<USkeletalMeshComponent>()->GetAnimInstance()->IsAnyMontagePlaying();
	Blackboard->SetValueAsBool(TEXT("MontagePlaying"), bMontagePlaying);
}

void ANPCAIController::FindPlayerByPerception()
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
