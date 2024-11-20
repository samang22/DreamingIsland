// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify/AnimNotify_Throw.h"
#include "Misc/Utils.h"
#include "Actors/Projectile/Projectile.h"
#include "Actors/Projectile/ProjectileTableRow.h"
#include "Actors/Link/Link.h"
#include "Actors/NPC/Cucco.h"
#include "Actors/Items/Item.h"
#include "Actors/Projectile/Bomb.h"

UAnimNotify_Throw::UAnimNotify_Throw()
{
}

void UAnimNotify_Throw::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
#if WITH_EDITOR
	if (GIsEditor && MeshComp->GetWorld() != GWorld) { return; } // 에디터 프리뷰
#endif

	ALink* Link = Cast<ALink>(MeshComp->GetOwner());
	check(Link);


	UWorld* World = Link->GetWorld();

	AProjectile* Projectile = World->SpawnActorDeferred<AProjectile>(AProjectile::StaticClass(),
		FTransform::Identity, Link, Link, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	FTransform NewTransform;
	Projectile->SetData(ProjectileName::Link_Throw, CollisionProfileName::BombProjectile);
	FVector NewLocation = Link->GetActorLocation();
	NewLocation.Z += LINK_LOCATION_OFFSET;
	NewTransform.SetLocation(NewLocation);
	NewTransform.SetRotation(Link->GetActorForwardVector().Rotation().Quaternion());
	Projectile->FinishSpawning(NewTransform);

	if (ACucco* Cucco = Cast<ACucco>(Link->GetCatchingActor()))
	{
		Cucco->Thrown();
		Link->ActorThrown();
	}
	else if (AItem* Item = Cast<AItem>(Link->GetCatchingActor()))
	{
		Link->ActorThrown();
	}
	else if (ABomb* Bomb = Cast<ABomb>(Link->GetCatchingActor()))
	{
		Link->ActorThrown();
	}

}
