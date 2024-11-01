// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify/NPC/AnimNotify_TSK_BeamSt_End.h"
#include "Actors/NPC/ToolShopKeeper.h"
UAnimNotify_TSK_BeamSt_End::UAnimNotify_TSK_BeamSt_End()
{
}

void UAnimNotify_TSK_BeamSt_End::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
#if WITH_EDITOR
	if (GIsEditor && MeshComp->GetWorld() != GWorld) { return; }
#endif
	AToolShopKeeper* TSK = Cast<AToolShopKeeper>(MeshComp->GetOwner());
	TSK->PlayMontage(NPC_MONTAGE::BEAM, true);
}
