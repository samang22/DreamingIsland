// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/CuccoAnimInstance.h"
#include "Actors/NPC/Cucco.h"
#include "Components/StatusComponent/NPCStatusComponent.h"
#include "Misc/Utils.h"

UCuccoAnimInstance::UCuccoAnimInstance()
{
}

void UCuccoAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	APawn* Pawn = TryGetPawnOwner();
	ACucco* Cucco = Cast<ACucco>(Pawn);
	StatusComponent = Cast<UNPCStatusComponent>(Cucco->GetStatusComponent());
}

void UCuccoAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (StatusComponent)
	{
		bIsWait = StatusComponent->GetAnimStatus(NPC_BIT_WAIT);
		bIsWalk = StatusComponent->GetAnimStatus(NPC_BIT_WALK);
		bIsRun = StatusComponent->GetAnimStatus(NPC_BIT_RUN);
		bIsLifted = StatusComponent->GetAnimStatus(NPC_BIT_LIFTED);
		bIsThrown = StatusComponent->GetAnimStatus(NPC_BIT_THROWN);
	}
}
