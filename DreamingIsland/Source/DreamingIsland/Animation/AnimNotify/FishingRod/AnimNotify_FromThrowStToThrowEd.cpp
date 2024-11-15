// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify/FishingRod/AnimNotify_FromThrowStToThrowEd.h"
#include "Actors/Weapon/FishingRod.h"
#include "Components/StatusComponent/FishingRodStatusComponent.h"
UAnimNotify_FromThrowStToThrowEd::UAnimNotify_FromThrowStToThrowEd()
{
}

void UAnimNotify_FromThrowStToThrowEd::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	AFishingRod* FishingRod = Cast<AFishingRod>(MeshComp->GetOwner());
	if (FishingRod) FishingRod->GetStatusComponent()->SetFishingRodStatus(FISHINGROD_STATUS::THROW_ED);
}

