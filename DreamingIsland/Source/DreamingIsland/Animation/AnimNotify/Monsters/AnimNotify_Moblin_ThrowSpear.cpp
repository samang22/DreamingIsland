// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify/Monsters/AnimNotify_Moblin_ThrowSpear.h"
#include "Misc/Utils.h"
#include "Actors/Projectile/Projectile.h"
#include "Actors/Projectile/ProjectileTableRow.h"
#include "Actors/Monster.h"

UAnimNotify_Moblin_ThrowSpear::UAnimNotify_Moblin_ThrowSpear()
{
}

void UAnimNotify_Moblin_ThrowSpear::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
#if WITH_EDITOR
	if (GIsEditor && MeshComp->GetWorld() != GWorld) { return; } // 에디터 프리뷰
#endif

	AMonster* Monster = Cast<AMonster>(MeshComp->GetOwner());
	check(Monster);

	const FVector MonsterForwardVector = Monster->GetActorForwardVector();
	const FVector WeaponLocation = MeshComp->GetSocketLocation(Monster_SocketName::Weapon);

	UWorld* World = Monster->GetWorld();

	AProjectile* Projectile = World->SpawnActorDeferred<AProjectile>(AProjectile::StaticClass(),
		FTransform::Identity, Monster, Monster, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	FTransform NewTransform;
	Projectile->SetData(ProjectileName::Moblin_SpearAttack, CollisionProfileName::MonsterProjectile);
	NewTransform.SetLocation(WeaponLocation);
	NewTransform.SetRotation(MonsterForwardVector.Rotation().Quaternion());
	Projectile->FinishSpawning(NewTransform);
}
