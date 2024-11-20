// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify/AnimNotify_ThrowLure.h"
#include "Misc/Utils.h"
#include "Actors/Projectile/Projectile.h"
#include "Actors/Projectile/ProjectileTableRow.h"
#include "Actors/Link/FishingLink.h"
#include "Actors/NPC/FishingLure.h"
#include "Components/StatusComponent/FishingLinkStatusComponent.h"

UAnimNotify_ThrowLure::UAnimNotify_ThrowLure()
{
}

void UAnimNotify_ThrowLure::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
#if WITH_EDITOR
	if (GIsEditor && MeshComp->GetWorld() != GWorld) { return; } // 에디터 프리뷰
#endif

	AFishingLink* Link = Cast<AFishingLink>(MeshComp->GetOwner());
	check(Link);


	UWorld* World = Link->GetWorld();

	AProjectile* Projectile = World->SpawnActorDeferred<AProjectile>(AProjectile::StaticClass(),
		FTransform::Identity, Link, Link, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	FTransform NewTransform;
	Projectile->SetData(ProjectileName::Link_Lure, CollisionProfileName::BombProjectile);
	FVector NewLocation = Link->GetActorLocation();
	NewLocation.Z += LINK_ITEM_OFFSET;
	NewTransform.SetLocation(NewLocation);
	NewTransform.SetRotation(Link->GetActorForwardVector().Rotation().Quaternion());
	Projectile->FinishSpawning(NewTransform);

	if (AFishingLure* Lure = Link->GetFishingLure())
	{
		Lure->SetFollowingActor(Projectile);
		Link->GetStatusComponent()->SetFishingLinkStatus(FISHINGLINK_STATUS::FISHING);
	}
}
