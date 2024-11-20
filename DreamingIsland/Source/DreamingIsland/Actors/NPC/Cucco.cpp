// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/NPC/Cucco.h"
#include "Misc/Utils.h"
#include "Components/StatusComponent/NPCStatusComponent.h"
#include "Components/AdvancedFloatingPawnMovement.h"
#include "Data/NPCTableRow.h"
#include "Actors/Link/Link.h"
#include "Actors/AI/PatrolPath.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

ACucco::ACucco(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	NPCName = NPC_Name_Korean::Cucco;
}

void ACucco::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsRun)
	{
		MovementComponent->RequestDirectMove(RunDirection * MovementComponent->GetMaxSpeed(), true);
		StatusComponent->SetOnAnimationStatus(NPC_BIT_RUN);
		//AddMovementInput(RunDirection, 100.f);
	}
	else
	{
		StatusComponent->SetOffAnimationStatus(NPC_BIT_RUN);
	}

	//CuccoCatchedSequence(DeltaTime);
}

void ACucco::BeginPlay()
{
	Super::BeginPlay();
}

void ACucco::SetIsCatched(bool _bIsCatched)
{
	bIsCatched = _bIsCatched;
	if (bIsCatched)
	{
		StatusComponent->SetOnAnimationStatus(NPC_BIT_LIFTED);
		StatusComponent->SetOffAnimationStatus(NPC_BIT_WALK);
	}
	else
	{
		StatusComponent->SetOffAnimationStatus(NPC_BIT_LIFTED);
		StatusComponent->SetOnAnimationStatus(NPC_BIT_WALK);
	}
}

void ACucco::StopMovement()
{
	MovementComponent->MaxSpeed = 0.f;
}

void ACucco::ResumeMovement()
{
	MovementComponent->MaxSpeed = NPCData->RushMovementMaxSpeed;
}

//void ACucco::CuccoCatchedSequence(float DeltaTime)
//{
//	if (bIsCatched)
//	{
//		StatusComponent->SetOnAnimationStatus(NPC_BIT_LIFTED);
//		if (CatchingCuccoActor)
//		{
//			ALink* Link = Cast<ALink>(CatchingCuccoActor);
//			if (Link)
//			{
//				FVector NewLocation = Link->GetActorLocation();
//				NewLocation.Z += LINK_LOCATION_OFFSET * 1.5;
//				SetActorLocation(NewLocation);
//			}
//			// Unvisible dummy projectile
//			else
//			{
//				// To prevent link stuck in the ground;
//				FVector OffsetVector = CatchingCuccoActor->GetActorLocation();
//				OffsetVector.Z += 20.f;
//				SetActorLocation(OffsetVector);
//			}
//
//		}
//	}
//	else
//	{
//		StatusComponent->SetOffAnimationStatus(NPC_BIT_LIFTED);
//	}
//}

void ACucco::SetCuccoRunWithDirection(FVector _Direction)
{
	bIsRun = true;
	RunDirection = _Direction;
}

void ACucco::SetCuccoRunEnd()
{
	bIsRun = false;
}

void ACucco::Thrown()
{
	StatusComponent->SetOnAnimationStatus(NPC_BIT_THROWN);
	StatusComponent->SetOffAnimationStatus(NPC_BIT_LIFTED);
}

void ACucco::Landed()
{
	StatusComponent->SetOffAnimationStatus(NPC_BIT_THROWN);
}
