// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster.h"
//#include "Animation/MonsterAnimInstance.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
//#include "Components/StatusComponent.h"
//#include "Misc/Utils.h"


UMonsterDataAsset::UMonsterDataAsset()
//	: AnimClass(UMonsterAnimInstance::StaticClass())

{
}


AMonster::AMonster(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;


	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));

	SkeletalMeshComponent->SetupAttachment(RootComponent);
	SkeletalMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementComponent"));
	//StatusComponent = CreateDefaultSubobject<UStatusComponent>(TEXT("StatusComponent"));
}

void AMonster::PostLoad()
{
}

// Called when the game starts or when spawned
void AMonster::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMonster::PostLoadSubobjects(FObjectInstancingGraph* OuterInstanceGraph)
{
}

void AMonster::OnConstruction(const FTransform& Transform)
{
}

// Called every frame
void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float AMonster::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	return 0.0f;
}

void AMonster::OnDie()
{
}


