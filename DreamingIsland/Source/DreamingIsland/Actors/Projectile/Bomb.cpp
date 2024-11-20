// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Projectile/Bomb.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Components/SphereComponent.h"
#include "Misc/Utils.h"
#include "Actors/Effect/ParticleEffect.h"
#include "Particles/ParticleSystem.h"
#include "Actors/Projectile/Projectile.h"


ABomb::ABomb()
{
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	CollisionComponent->SetCollisionProfileName(CollisionProfileName::BombProjectile);
	CollisionComponent->SetSphereRadius(48.f);
	CollisionComponent->OnComponentHit.AddDynamic(this, &ThisClass::OnHit);
	RootComponent = CollisionComponent;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshObj(TEXT("/Script/Engine.StaticMesh'/Game/Assets/Item/Bomb/Bomb.Bomb'"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	if (StaticMeshObj.Object)
	{
		StaticMeshComponent->SetStaticMesh(StaticMeshObj.Object);
	}
	StaticMeshComponent->SetWorldScale3D(FVector(90.0, 90.0, 90.0));
	StaticMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	//static ConstructorHelpers::FObjectFinder<UPhysicalMaterial> PhysMaterial(TEXT("/Script/PhysicsCore.PhysicalMaterial'/Game/Assets/Item/PM_Item.PM_Item'"));
	//PhysicalMaterial = PhysMaterial.Object;

	
}

void ABomb::BeginPlay()
{
	Super::BeginPlay();
	CollisionComponent->bHiddenInGame = COLLISION_HIDDEN_IN_GAME;
	CollisionComponent->SetSphereRadius(36.f);
}
void ABomb::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Explosion();
	Destroy();
}
void ABomb::Explosion()
{
	UWorld* World = this->GetWorld();

	AParticleEffect* Effect = World->SpawnActorDeferred<AParticleEffect>(AParticleEffect::StaticClass(),
		FTransform::Identity, nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);


	static UParticleSystem* ParticleSystem = LoadObject<UParticleSystem>(nullptr, TEXT("/Script/Engine.ParticleSystem'/Game/Assets/FXVarietyPack/Particles/P_ky_explosion.P_ky_explosion'"));
	if (ParticleSystem) Effect->SetParticleSystem(ParticleSystem);
	Effect->SetLifeTime(3.f);
	FTransform NewTransform;
	NewTransform.SetLocation(GetActorLocation());
	NewTransform.SetRotation(FRotator::ZeroRotator.Quaternion());
	Effect->FinishSpawning(NewTransform);
}
void ABomb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABomb::SpawnProjectile()
{
	UWorld* World = GetWorld();

	AProjectile* Projectile = World->SpawnActorDeferred<AProjectile>(AProjectile::StaticClass(),
		FTransform::Identity, nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	FTransform NewTransform;
	Projectile->SetData(ProjectileName::Bomber_Bomb, CollisionProfileName::LinkProjectile);
	NewTransform.SetLocation(GetActorLocation());
	NewTransform.SetRotation(FRotator::ZeroRotator.Quaternion());
	Projectile->FinishSpawning(NewTransform);
}