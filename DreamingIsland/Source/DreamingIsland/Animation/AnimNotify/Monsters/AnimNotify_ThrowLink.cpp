// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify/Monsters/AnimNotify_ThrowLink.h"
#include "Misc/Utils.h"
#include "Actors/Projectile/Projectile.h"
#include "Actors/Projectile/ProjectileTableRow.h"
#include "Actors/Monster.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Components/HinoxStatusComponent.h"
#include "Actors/Link.h"


UAnimNotify_ThrowLink::UAnimNotify_ThrowLink()
{
}

void UAnimNotify_ThrowLink::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
#if WITH_EDITOR
	if (GIsEditor && MeshComp->GetWorld() != GWorld) { return; }
#endif

	AMonster* Monster = Cast<AMonster>(MeshComp->GetOwner());
	ACharacter* Character = UGameplayStatics::GetPlayerCharacter(Monster->GetWorld(), 0);
	ALink* Link = Cast<ALink>(Character);


	const FVector MonsterForwardVector = Monster->GetActorForwardVector();
	FVector MonsterShootDirection = MonsterForwardVector;
	MonsterShootDirection.Z = 1.f;
	MonsterShootDirection.Normalize();

	const FVector WeaponLocation = MeshComp->GetSocketLocation(Monster_SocketName::Weapon);

	UWorld* World = Monster->GetWorld();

	AProjectile* Projectile = World->SpawnActorDeferred<AProjectile>(AProjectile::StaticClass(),
		FTransform::Identity, Monster, Monster, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	FTransform NewTransform;
	Projectile->SetData(ProjectileName::Hinox_Link, CollisionProfileName::BombProjectile, COLLISION_CHANNEL_BOMBPROJECTILE);
	NewTransform.SetLocation(WeaponLocation);
	NewTransform.SetRotation(MonsterShootDirection.Rotation().Quaternion());
	Projectile->FinishSpawning(NewTransform);

	Link->SetCatchingLinkActor(Projectile);

	UHinoxStatusComponent* HinoxStatusComponent = Cast<UHinoxStatusComponent>(Monster->GetStatusComponent());
	HinoxStatusComponent->SetIsCatching(false);
}
