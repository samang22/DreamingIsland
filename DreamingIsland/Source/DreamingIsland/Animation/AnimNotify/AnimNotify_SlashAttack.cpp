// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify/AnimNotify_SlashAttack.h"
#include "Misc/Utils.h"
#include "Actors/Projectile/Projectile.h"
UAnimNotify_SlashAttack::UAnimNotify_SlashAttack()
{
}

void UAnimNotify_SlashAttack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
#if WITH_EDITOR
	if (GIsEditor && MeshComp->GetWorld() != GWorld) { return; } // 에디터 프리뷰
#endif

	APawn* OwningPawn = Cast<APawn>(MeshComp->GetOwner());
	check(OwningPawn);

	const FVector SwordTopLocation = MeshComp->GetSocketLocation(Link_SocketName::SwordTop);

	UWorld* World = OwningPawn->GetWorld();
	//AProjectile* Projectile = World->SpawnActorDeferred<AProjectile>(ProjectileTableRow->ProjectileClass,
	//	FTransform::Identity, OwningPawn, OwningPawn, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	//Projectile->SetData(GunTableRow->ProjectileRowHandle);

	//FTransform NewTransform;
	//
	//NewTransform.SetLocation(MuzzleLocation);
	//NewTransform.SetRotation(FRotator::ZeroRotator.Quaternion());
	//Projectile->FinishSpawning(NewTransform);
}
