// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify/FishingRod/AnimNotify_FromThrowEdToIdle.h"
#include "Actors/Weapon/FishingRod.h"
#include "Components/StatusComponent/FishingRodStatusComponent.h"
UAnimNotify_FromThrowEdToIdle::UAnimNotify_FromThrowEdToIdle()
{
}

void UAnimNotify_FromThrowEdToIdle::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	AFishingRod* FishingRod = Cast<AFishingRod>(MeshComp->GetOwner());
	if (FishingRod)	FishingRod->GetStatusComponent()->SetFishingRodStatus(FISHINGROD_STATUS::IDLE);
}
