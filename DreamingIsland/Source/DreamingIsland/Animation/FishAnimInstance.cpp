// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/FishAnimInstance.h"
#include "Actors/NPC/Fish.h"
#include "Components/StatusComponent/FishStatusComponent.h"

void UFishAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	APawn* Pawn = TryGetPawnOwner();
	if (!Pawn) return;

	AFish* Fish = Cast<AFish>(Pawn);
	StatusComponent = Fish->GetStatusComponent();
}

void UFishAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (StatusComponent)
	{
		bIsWait = StatusComponent->GetAnimStatus(FISH_BIT_WAIT);
		bIsPokeWaiting = StatusComponent->GetAnimStatus(FISH_BIT_POKEWAIT);
		bIsCatch = StatusComponent->GetAnimStatus(FISH_BIT_CATCHING);
		bIsGet = StatusComponent->GetAnimStatus(FISH_BIT_GET);
	}
}
