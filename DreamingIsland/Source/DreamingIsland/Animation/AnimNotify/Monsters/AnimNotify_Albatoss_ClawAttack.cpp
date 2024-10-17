// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify/Monsters/AnimNotify_Albatoss_ClawAttack.h"
#include "Animation/AlbatossAnimInstance.h"
#include "Misc/Utils.h"
#include "Actors/Projectile/Projectile.h"
#include "Actors/Projectile/ProjectileTableRow.h"

UAnimNotify_Albatoss_ClawAttack::UAnimNotify_Albatoss_ClawAttack()
{
}
void UAnimNotify_Albatoss_ClawAttack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
#if WITH_EDITOR
	if (GIsEditor && MeshComp->GetWorld() != GWorld) { return; } // 에디터 프리뷰
#endif
	if (ProjectileTableRowHandle.IsNull()) { return; }
	FProjectileTableRow* Data = ProjectileTableRowHandle.GetRow<FProjectileTableRow>(TEXT("Link_SlashAttack"));
	if (!Data) { ensure(false); return; }

	APawn* OwningPawn = Cast<APawn>(MeshComp->GetOwner());
	check(OwningPawn);

	const FVector SwordTopLocation = MeshComp->GetSocketLocation(Link_SocketName::SwordTop);

	UWorld* World = OwningPawn->GetWorld();
	AProjectile* Projectile = World->SpawnActorDeferred<AProjectile>(Data->ProjectileClass,
		FTransform::Identity, OwningPawn, OwningPawn, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	FTransform NewTransform;
	Projectile->SetData(ProjectileTableRowHandle, FString(Link_SocketName_FString::SwordTop), CollisionProfileName::Monster_Projectile);
	NewTransform.SetLocation(SwordTopLocation);
	NewTransform.SetRotation(FRotator::ZeroRotator.Quaternion());
	Projectile->FinishSpawning(NewTransform);
}
