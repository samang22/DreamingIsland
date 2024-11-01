// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify/NPC/AnimNotify_TSK_BeamEnd.h"
#include "AnimNotify_TSK_BeamEnd.h"
#include "Actors/NPC/ToolShopKeeper.h"

UAnimNotify_TSK_BeamEnd::UAnimNotify_TSK_BeamEnd()
{
}

void UAnimNotify_TSK_BeamEnd::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	if (!TSK)
	{
		TSK = Cast<AToolShopKeeper>(MeshComp->GetOwner());
	}

	if (TSK && TSK->GetIsShootBeam())
	{
		TSK->PlayMontage(NPC_MONTAGE::BEAM);
	}
}
