// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/FishingRodAnimInstance.h"
#include "Actors/Weapon/FishingRod.h"

void UFishingRodAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	APawn* Pawn = TryGetPawnOwner();
	if (!Pawn) return;

	AFishingRod* FishingRod = Cast<AFishingRod>(Pawn);
	StatusComponent = FishingRod->GetStatusComponent();
}

void UFishingRodAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
}
