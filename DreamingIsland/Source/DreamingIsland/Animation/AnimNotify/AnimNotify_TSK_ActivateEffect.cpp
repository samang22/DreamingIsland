// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify/AnimNotify_TSK_ActivateEffect.h"
#include "Actors/NPC/ToolShopKeeper.h"

UAnimNotify_TSK_ActivateEffect::UAnimNotify_TSK_ActivateEffect()
{
}

void UAnimNotify_TSK_ActivateEffect::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	AToolShopKeeper* ToolShopKeeper = Cast<AToolShopKeeper>(MeshComp->GetOwner());
	if (ToolShopKeeper) ToolShopKeeper->ActivateEffect();
}
