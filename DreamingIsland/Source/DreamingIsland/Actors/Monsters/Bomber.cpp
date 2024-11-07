// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Monsters/Bomber.h"
#include "Actors/Projectile/Projectile.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Misc/Utils.h"
#include "Particles/ParticleSystemComponent.h"
#include "Particles/ParticleSystem.h"
#include "Actors/Effect/ParticleEffect.h"
#include "Data/PawnTableRow.h"


ABomber::ABomber(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UTexture> TextureObject_Default(TEXT("/Script/Engine.Texture2D'/Game/Assets/Monsters/BomberGreen/MI_face_alb_0.MI_face_alb_0'"));
	static ConstructorHelpers::FObjectFinder<UTexture> TextureObject_Smile(TEXT("/Script/Engine.Texture2D'/Game/Assets/Monsters/BomberGreen/MI_face_alb_1.MI_face_alb_1'"));
	static ConstructorHelpers::FObjectFinder<UTexture> TextureObject_1(TEXT("/Script/Engine.Texture2D'/Game/Assets/Monsters/BomberGreen/MI_face_alb_4.MI_face_alb_4'")); 
	static ConstructorHelpers::FObjectFinder<UTexture> TextureObject_2(TEXT("/Script/Engine.Texture2D'/Game/Assets/Monsters/BomberGreen/MI_face_alb_3.MI_face_alb_3'"));
	static ConstructorHelpers::FObjectFinder<UTexture> TextureObject_3(TEXT("/Script/Engine.Texture2D'/Game/Assets/Monsters/BomberGreen/MI_face_alb_2.MI_face_alb_2'"));

	Texture_Default = TextureObject_Default.Object;
	Texture_Smile = TextureObject_Smile.Object;
	Texture_1 = TextureObject_1.Object;
	Texture_2 = TextureObject_2.Object;
	Texture_3 = TextureObject_3.Object;

	//static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("/Script/Engine.ParticleSystem'/Game/Assets/Realistic_Starter_VFX_Pack_Vol2/Particles/Explosion/P_Explosion_Big_A.P_Explosion_Big_A'"));
	//ExplosionEffectComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ExplosionEffectComponent"));
	//ExplosionEffectComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	//if (ParticleAsset.Object)
	//{
	//	ExplosionEffectComponent->SetTemplate(ParticleAsset.Object);
	//}
	//ExplosionEffectComponent->bAutoActivate = false;
}
  
void ABomber::BeginPlay()
{
	Super::BeginPlay();
	MaterialInterface = SkeletalMeshComponent->GetMaterial(1);
	DynamicMaterialInstance = UMaterialInstanceDynamic::Create(MaterialInterface, this);
	DynamicMaterialInstance->SetTextureParameterValue(TEXT("TextureParameter"), Texture_Default);
	SkeletalMeshComponent->SetMaterial(1, DynamicMaterialInstance);


	AISenseConfig_Sight->SightRadius = 10000.f;
	AISenseConfig_Sight->LoseSightRadius = 10000.f;
	AISenseConfig_Sight->PeripheralVisionAngleDegrees = 359.9f;

}

void ABomber::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ElapsedTime += DeltaTime;

	if (ElapsedTime < 2.f)
	{
		DynamicMaterialInstance->SetTextureParameterValue(TEXT("TextureParameter"), Texture_Smile);
	}
	else if (2.f <= ElapsedTime && ElapsedTime < 3.f)
	{
		DynamicMaterialInstance->SetTextureParameterValue(TEXT("TextureParameter"), Texture_3);
	}
	else if (3.f <= ElapsedTime && ElapsedTime < 4.f)
	{
		DynamicMaterialInstance->SetTextureParameterValue(TEXT("TextureParameter"), Texture_2);
	}
	else if (4.f <= ElapsedTime && ElapsedTime < 5.f)
	{
		DynamicMaterialInstance->SetTextureParameterValue(TEXT("TextureParameter"), Texture_1);
	}
	else
	{
		SpawnExplosionEffect();
		SpawnProjectileAndDestory();
	}
}

void ABomber::SpawnProjectileAndDestory()
{
	UWorld* World = GetWorld();

	AProjectile* Projectile = World->SpawnActorDeferred<AProjectile>(AProjectile::StaticClass(),
		FTransform::Identity, nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	FTransform NewTransform;
	Projectile->SetData(ProjectileName::Bomber_Bomb, CollisionProfileName::MonsterProjectile);
	NewTransform.SetLocation(GetActorLocation());
	NewTransform.SetRotation(FRotator::ZeroRotator.Quaternion());
	Projectile->FinishSpawning(NewTransform);
	Destroy();
}

void ABomber::SpawnExplosionEffect()
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
