// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify/Monsters/AnimNotify_UnequipWeapon.h"
#include "Actors/Monster.h"

UAnimNotify_UnequipWeapon::UAnimNotify_UnequipWeapon()
{
}

void UAnimNotify_UnequipWeapon::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	AMonster* Monster = Cast<AMonster>(MeshComp->GetOwner());
	check(Monster);
	Monster->RenderOffWeapon();
	Monster->SetWeaponUnEquiped();

}
