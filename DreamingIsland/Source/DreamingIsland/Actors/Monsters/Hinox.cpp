// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Monsters/Hinox.h"
#include "Components/StatusComponent/HinoxStatusComponent.h"
#include "Data/PawnTableRow.h"
#include "Actors/Effect/ParticleEffect.h"
#include "Actors/Effect/NiagaraEffect.h"
#include "Kismet/GameplayStatics.h"


AHinox::AHinox(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	StatusComponent = CreateDefaultSubobject<UHinoxStatusComponent>(TEXT("HinoxStatusComponent"));
}

void AHinox::BeginPlay()
{
	Super::BeginPlay();
	RenderOffWeapon();
	SetWeaponUnEquiped();
}

void AHinox::OnDie()
{
	if (MonsterData->bUseParticleEffect)
	{
		UWorld* World = this->GetWorld();

		AParticleEffect* Effect = World->SpawnActorDeferred<AParticleEffect>(AParticleEffect::StaticClass(),
			FTransform::Identity, nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

		FTransform NewTransform;
		Effect->SetData(MonsterData->ParticleEffectTableRowHandle);
		NewTransform.SetLocation(GetActorLocation());
		NewTransform.SetRotation(FRotator::ZeroRotator.Quaternion());
		Effect->FinishSpawning(NewTransform);
	}

	if (MonsterData->bUseNiagaraEffect)
	{
		UWorld* World = this->GetWorld();

		ANiagaraEffect* Effect = World->SpawnActorDeferred<ANiagaraEffect>(ANiagaraEffect::StaticClass(),
			FTransform::Identity, nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

		FTransform NewTransform;
		Effect->SetData(MonsterData->NiagaraEffectTableRowHandle);
		NewTransform.SetLocation(GetActorLocation());
		NewTransform.SetRotation(FRotator::ZeroRotator.Quaternion());
		Effect->FinishSpawning(NewTransform);
	}

	UGameplayStatics::OpenLevel(GetWorld(), TEXT("Ending"));
}
