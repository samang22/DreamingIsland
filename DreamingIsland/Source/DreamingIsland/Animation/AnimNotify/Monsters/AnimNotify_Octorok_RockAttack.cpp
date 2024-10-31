// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify/Monsters/AnimNotify_Octorok_RockAttack.h"
#include "Misc/Utils.h"
#include "Actors/Projectile/Projectile.h"
#include "Actors/Projectile/ProjectileTableRow.h"
#include "Actors/Monsters/Monster.h"
UAnimNotify_Octorok_RockAttack::UAnimNotify_Octorok_RockAttack()
{
}

void UAnimNotify_Octorok_RockAttack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
#if WITH_EDITOR
	if (GIsEditor && MeshComp->GetWorld() != GWorld) { return; } // 에디터 프리뷰
#endif

	AMonster* Monster = Cast<AMonster>(MeshComp->GetOwner());
	check(Monster);

	const FVector MonsterForwardVector = Monster->GetActorForwardVector();

	UWorld* World = Monster->GetWorld();

	AProjectile* Projectile = World->SpawnActorDeferred<AProjectile>(AProjectile::StaticClass(),
		FTransform::Identity, Monster, Monster, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	FTransform NewTransform;
	Projectile->SetData(ProjectileName::Octorok_RockAttack, CollisionProfileName::MonsterProjectile);
	NewTransform.SetLocation(Monster->GetActorLocation() + OCTOROK_ROCKATTACK_LENGTH * MonsterForwardVector);
	NewTransform.SetRotation(Monster->GetActorRotation().Quaternion());
	Projectile->FinishSpawning(NewTransform);
}
