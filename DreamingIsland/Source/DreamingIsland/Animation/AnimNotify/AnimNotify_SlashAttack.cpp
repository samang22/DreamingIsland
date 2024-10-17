// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify/AnimNotify_SlashAttack.h"
#include "Misc/Utils.h"
#include "Actors/Projectile/Projectile.h"
#include "Actors/Projectile/ProjectileTableRow.h"
#include "Actors/Link.h"

UAnimNotify_SlashAttack::UAnimNotify_SlashAttack()
{
}

void UAnimNotify_SlashAttack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
#if WITH_EDITOR
	if (GIsEditor && MeshComp->GetWorld() != GWorld) { return; } // 에디터 프리뷰
#endif

	ALink* Link = Cast<ALink>(MeshComp->GetOwner());
	check(Link);

	const FVector SwordTopLocation = MeshComp->GetSocketLocation(Link_SocketName::SwordTop);

	const FDataTableRowHandle Handle = Link->GetProjectileTableRowHandle();


	UWorld* World = Link->GetWorld();
	
	FProjectileTableRow* Data = Handle.GetRow<FProjectileTableRow>(TEXT("Link_SlashAttack"));
	AProjectile* Projectile = World->SpawnActorDeferred<AProjectile>(Data->ProjectileClass,
		FTransform::Identity, Link, Link, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	FTransform NewTransform;
	Projectile->SetData(ProjectileTableRowHandle, TEXT("Link_SlashAttack"), CollisionProfileName::Link_Projectile);
	NewTransform.SetLocation(Link->GetActorLocation());
	NewTransform.SetRotation(FRotator::ZeroRotator.Quaternion());
	Projectile->FinishSpawning(NewTransform);
}
