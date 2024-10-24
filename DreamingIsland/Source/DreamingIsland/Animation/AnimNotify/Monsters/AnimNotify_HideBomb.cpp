// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify/Monsters/AnimNotify_HideBomb.h"
#include "Actors/Monster.h"

UAnimNotify_HideBomb::UAnimNotify_HideBomb()
{
}

void UAnimNotify_HideBomb::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
#if WITH_EDITOR
	if (GIsEditor && MeshComp->GetWorld() != GWorld) { return; } // 에디터 프리뷰
#endif

	AMonster* Monster = Cast<AMonster>(MeshComp->GetOwner());
	check(Monster);
	Monster->SetWeaponUnEquiped();
	Monster->RenderOffWeapon();
}
