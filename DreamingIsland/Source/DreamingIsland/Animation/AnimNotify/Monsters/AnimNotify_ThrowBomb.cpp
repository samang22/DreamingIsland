// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify/Monsters/AnimNotify_ThrowBomb.h"
#include "Misc/Utils.h"
#include "Actors/Projectile/Projectile.h"
#include "Actors/Projectile/ProjectileTableRow.h"
#include "Actors/Monster.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

UAnimNotify_ThrowBomb::UAnimNotify_ThrowBomb()
{
}

void UAnimNotify_ThrowBomb::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
#if WITH_EDITOR
	if (GIsEditor && MeshComp->GetWorld() != GWorld) { return; } 
#endif

	AMonster* Monster = Cast<AMonster>(MeshComp->GetOwner());

	const FVector MonsterForwardVector = Monster->GetActorForwardVector();
	FVector MonsterShootDirection = MonsterForwardVector;
	MonsterShootDirection.Z = 1.f;
	MonsterShootDirection.Normalize();

	const FVector WeaponLocation = MeshComp->GetSocketLocation(Monster_SocketName::Weapon);

	UWorld* World = Monster->GetWorld();

	AProjectile* Projectile = World->SpawnActorDeferred<AProjectile>(AProjectile::StaticClass(),
		FTransform::Identity, Monster, Monster, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	FTransform NewTransform;
	Projectile->SetData(ProjectileName::Hinox_Bomb, CollisionProfileName::BombProjectile, COLLISION_CHANNEL_MONSTERPROJECTILE);
	NewTransform.SetLocation(WeaponLocation);
	NewTransform.SetRotation(MonsterShootDirection.Rotation().Quaternion());
	Projectile->FinishSpawning(NewTransform);
}
