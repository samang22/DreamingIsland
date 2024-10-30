// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/AI/Monsters/BasicMonsterAIController.h"
#include "Actors/Monster.h"
#include "GameFramework/Character.h"
#include "Components/StatusComponent.h"
#include "Components/SplineComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Decorators/BTDecorator_IsAtLocation.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Data/PawnTableRow.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"


void ABasicMonsterAIController::BeginPlay()
{
	Super::BeginPlay();
	if (!IsValid(PatrolPath))
	{
		//checkf(false, TEXT("PatrolPath not valid"));
		return;
	}

	UBehaviorTree* BehaviorTree = nullptr;
	if (!IsValid(BrainComponent))
	{
		BehaviorTree = LoadObject<UBehaviorTree>(nullptr, TEXT("/Script/AIModule.BehaviorTree'/Game/Blueprint/AI/Monster/BT_BasicMonster.BT_BasicMonster'"));
		check(BehaviorTree);
		RunBehaviorTree(BehaviorTree);
	}

	Blackboard->SetValueAsObject(TEXT("SplineComponent"), PatrolPath);
}

void ABasicMonsterAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	StatusComponentRef = InPawn->GetComponentByClass<UStatusComponent>();
	StatusComponentRef->OnHPChanged.AddDynamic(this, &ThisClass::OnDamaged);
}

void ABasicMonsterAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!Blackboard) return;

	APawn* OwningPawn = GetPawn();

	// Montage가 Play 중이라면 BT 내부에서 AI 진행을 멈춘다
	const bool bMontagePlaying = OwningPawn->GetComponentByClass<USkeletalMeshComponent>()->GetAnimInstance()->IsAnyMontagePlaying();


	Blackboard->SetValueAsBool(TEXT("MontagePlaying"), bMontagePlaying);

	if (!bDamaged)
	{
		FindPlayerByPerception();
	}




}

void ABasicMonsterAIController::OnDamaged(float CurrentHP, float MaxHP)
{
	bDamaged = true;
	AController* Instigator_ = StatusComponentRef->GetLastInstigator();
	APawn* InstigatorPawn = Instigator_->GetPawn();
	check(InstigatorPawn);
	Blackboard->SetValueAsObject(TEXT("DetectedPlayer"), Cast<UObject>(InstigatorPawn));
	UKismetSystemLibrary::K2_SetTimer(this, TEXT("ResetOnDamaged"), 10.f, false);
}

void ABasicMonsterAIController::ResetOnDamaged()
{
	bDamaged = false;
}

void ABasicMonsterAIController::FindPlayerByPerception()
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
