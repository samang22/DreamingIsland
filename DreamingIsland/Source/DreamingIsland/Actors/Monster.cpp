// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster.h"
#include "Animation/MonsterAnimInstance.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Data/PawnTableRow.h"
#include "Components/StatusComponent.h"
#include "Misc/Utils.h"


UMonsterDataAsset::UMonsterDataAsset()
	: AnimClass(UMonsterAnimInstance::StaticClass())

{
}


AMonster::AMonster(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	PrimaryActorTick.bCanEverTick = true;

	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementComponent"));
	StatusComponent = CreateDefaultSubobject<UStatusComponent>(TEXT("StatusComponent"));



	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	//CollisionComponent->RegisterComponent();
	//CollisionComponent->SetCollisionProfileName(CollisionProfileName::Monster);
	CollisionComponent->SetCanEverAffectNavigation(false);
	RootComponent = CollisionComponent;


	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	SkeletalMeshComponent->SetupAttachment(RootComponent);
	SkeletalMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AMonster::SetData(const FDataTableRowHandle& InDataTableRowHandle, FString Key)
{
	DataTableRowHandle = InDataTableRowHandle;
	if (DataTableRowHandle.IsNull()) { return; }
	FPawnTableRow* Data = DataTableRowHandle.GetRow<FPawnTableRow>(Key);
	if (!Data) { ensure(false); return; }
	MonsterData = Data;

	MovementComponent->MaxSpeed = MonsterData->MovementMaxSpeed;

	MonsterData = Data;
	if (IsValid(CollisionComponent))
	{
		USphereComponent* SphereComponent = Cast<USphereComponent>(CollisionComponent);
		SphereComponent->SetSphereRadius(MonsterData->CollisionSphereRadius);
	}

	SkeletalMeshComponent->SetSkeletalMesh(MonsterData->SkeletalMesh);
	SkeletalMeshComponent->SetAnimClass(MonsterData->AnimClass);
	SkeletalMeshComponent->SetRelativeTransform(MonsterData->MeshTransform);
}



void AMonster::PostLoad()
{
	Super::PostLoad();
}

// Called when the game starts or when spawned
void AMonster::BeginPlay()
{
	Super::BeginPlay();
	//SetData(DataTableRowHandle);
	// SetData will be called by Subclasses
}

void AMonster::PostLoadSubobjects(FObjectInstancingGraph* OuterInstanceGraph)
{
	Super::PostLoadSubobjects(OuterInstanceGraph);
}

void AMonster::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	SetData(DataTableRowHandle, MonsterName);
	SetActorTransform(Transform);
}

void AMonster::PostDuplicate(EDuplicateMode::Type DuplicateMode)
{
	Super::PostDuplicate(DuplicateMode);

	if (DuplicateMode == EDuplicateMode::Normal)
	{
		FTransform Backup = GetActorTransform();
		CollisionComponent->DestroyComponent();
		SetData(DataTableRowHandle, MonsterName);
		SetActorTransform(Backup);
	}
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

void AMonster::Attack()
{
	if (AttackMontage)
	{
		//StatusComponent->SetOnAnimationStatus(LINK_BIT_SLASH);
		//AnimInstance->PlaySlashMontage();
	}
}


