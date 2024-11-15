// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Task/Fish/BTTask_FishFighting.h"
#include "Actors/NPC/Fish.h"
#include "Misc/Utils.h"
#include "Components/StatusComponent/FishStatusComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

UBTTask_FishFighting::UBTTask_FishFighting()
{
	NodeName = "FishFighting";
	bCreateNodeInstance = true;
	bTickIntervals = true;
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_FishFighting::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	BehaviorTreeComponent = &OwnerComp;
	BlackboardComponent = OwnerComp.GetBlackboardComponent();

	AFish* Fish = Cast<AFish>(AIOwner->GetPawn());
	if (!Fish)
	{
		return EBTNodeResult::Failed;
	}
	if (FISH_STATUS::FIGHTING != Fish->GetStatusComponent()->GetFishStatus())
	{
		return EBTNodeResult::Failed;
	}

	return EBTNodeResult::InProgress;
}

void UBTTask_FishFighting::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	UE_LOG(LogTemp, Warning, TEXT("FishFighting"));


	AActor* Lure = Cast<AActor>(BlackboardComponent->GetValueAsObject(TEXT("DetectedLure")));
	AFish* Fish = Cast<AFish>(AIOwner->GetPawn());
	ACharacter* Character = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (!Lure || !Fish || !Character)
	{
		FinishLatentTask(*BehaviorTreeComponent, EBTNodeResult::Failed);
		return;
	}
	FVector ToLinkDirection = Character->GetActorLocation() - Fish->GetActorLocation();
	ToLinkDirection.Normalize();

	FVector ToLureDirection = Lure->GetActorLocation() - Fish->GetActorLocation();
	ToLureDirection.Normalize();

	FVector FinalDirection = (ToLinkDirection + ToLureDirection) / 2.0;
	FinalDirection.Normalize();

	Fish->SetDesiredDirection(FinalDirection);

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
	Fish->AddForce(FinalDirection * Force * -1);

	if (FVector::Dist(Lure->GetActorLocation(), Fish->GetActorLocation()) > FISH_AISENSECONFIG_SIGHT_LOSESIGHTRADIUS)
	{
		FinishLatentTask(*BehaviorTreeComponent, EBTNodeResult::Failed);
	}
	FinishLatentTask(*BehaviorTreeComponent, EBTNodeResult::InProgress);
}
