// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify/Monsters/AnimNotify_CatchLink.h"
#include "Misc/Utils.h"
#include "Actors/Projectile/Projectile.h"
#include "Actors/Projectile/ProjectileTableRow.h"
#include "Actors/Monster.h"

UAnimNotify_CatchLink::UAnimNotify_CatchLink()
{
}

void UAnimNotify_CatchLink::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
#if WITH_EDITOR
	if (GIsEditor && MeshComp->GetWorld() != GWorld) { return; }
#endif

	AMonster* Monster = Cast<AMonster>(MeshComp->GetOwner());

	const FVector WeaponLocation = MeshComp->GetSocketLocation(Monster_SocketName::Weapon);

	UWorld* World = Monster->GetWorld();

	AProjectile* Projectile = World->SpawnActorDeferred<AProjectile>(AProjectile::StaticClass(),
		FTransform::Identity, Monster, Monster, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	FTransform NewTransform;
	Projectile->SetData(ProjectileName::Hinox_Catch, CollisionProfileName::MonsterProjectile, COLLISION_CHANNEL_MONSTERPROJECTILE);
	NewTransform.SetLocation(WeaponLocation);
	NewTransform.SetRotation(FVector::Zero().Rotation().Quaternion());
	Projectile->FinishSpawning(NewTransform);
}
