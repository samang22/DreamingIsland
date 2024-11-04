// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/AI/BaseAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Decorators/BTDecorator_IsAtLocation.h"
#include "Components/SplineComponent.h"
#include "Components/StatusComponent/StatusComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Actors/Monsters/Monster.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Data/PawnTableRow.h"

void ABaseAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void ABaseAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseAIController::SetPatrolPath(TObjectPtr<USplineComponent> NewPatrolPath)
{
	PatrolPath = NewPatrolPath;
}
