// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Animation/MonsterAnimInstance.h"
#include "Components/AdvancedFloatingPawnMovement.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Data/PawnTableRow.h"
#include "Components/MonsterStatusComponent.h"
#include "Misc/Utils.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Actors/AI/PatrolPath.h"
#include "Actors/AI/BasicMonsterAIController.h"
#include "Kismet/KismetMathLibrary.h"

UMonsterDataAsset::UMonsterDataAsset()
	: AnimClass(UMonsterAnimInstance::StaticClass())

{
}


AMonster::AMonster(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	PrimaryActorTick.bCanEverTick = true;

	MovementComponent = CreateDefaultSubobject<UAdvancedFloatingPawnMovement>(TEXT("MovementComponent"));
	StatusComponent = CreateDefaultSubobject<UMonsterStatusComponent>(TEXT("StatusComponent"));



	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	CollisionComponent->SetCollisionProfileName(CollisionProfileName::Monster);

	CollisionComponent->SetCanEverAffectNavigation(false);
	RootComponent = CollisionComponent;

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	SkeletalMeshComponent->SetupAttachment(RootComponent);

	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));
	AISenseConfig_Sight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("AISenseConfig_Sight"));
	AISenseConfig_Sight->DetectionByAffiliation.bDetectNeutrals = true;
	AISenseConfig_Sight->SightRadius = AISENSECONFIG_SIGHT_SIGHTRADIUS;
	AISenseConfig_Sight->LoseSightRadius = AISENSECONFIG_SIGHT_LOSESIGHTRADIUS;
	AISenseConfig_Sight->PeripheralVisionAngleDegrees = AISENSECONFIG_SIGHT_LOSESIGHTRADIUS_PERIPHERALVISIONANGLEDEGREES;
	AIPerceptionComponent->ConfigureSense(*AISenseConfig_Sight);
}

void AMonster::SetData(const FDataTableRowHandle& InDataTableRowHandle, FString Key)
{
	DataTableRowHandle = InDataTableRowHandle;
	if (DataTableRowHandle.IsNull()) { return; }
	FPawnTableRow* Data = DataTableRowHandle.GetRow<FPawnTableRow>(Key);
	if (!Data) { return; }
	MonsterData = Data;


	if (IsValid(CollisionComponent))
	{
		USphereComponent* SphereComponent = Cast<USphereComponent>(CollisionComponent);
		SphereComponent->SetSphereRadius(MonsterData->CollisionSphereRadius);
		CollisionComponent->SetCollisionProfileName(CollisionProfileName::Monster);
		CollisionComponent->bHiddenInGame = false;
		CollisionComponent->RegisterComponent();

	}

	SkeletalMeshComponent->SetSkeletalMesh(MonsterData->SkeletalMesh);
	SkeletalMeshComponent->SetAnimClass(MonsterData->AnimClass);
	SkeletalMeshComponent->SetRelativeTransform(MonsterData->MeshTransform);
	FRotator NewRotator = FRotator(0.0, 0.0, 0.0);
	SkeletalMeshComponent->SetWorldRotation(NewRotator.Quaternion());
	MovementComponent->MaxSpeed = MonsterData->MovementMaxSpeed;

	AIControllerClass = MonsterData->AIControllerClass;
}



void AMonster::PostLoad()
{
	Super::PostLoad();
}
void AMonster::PostLoadSubobjects(FObjectInstancingGraph* OuterInstanceGraph)
{
	Super::PostLoadSubobjects(OuterInstanceGraph);
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

void AMonster::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (PatrolPathRef)
	{
		if (ABasicMonsterAIController* BasicMonsterAIController = Cast<ABasicMonsterAIController>(Controller))
		{
			BasicMonsterAIController->SetPatrolPath(PatrolPathRef->GetPath());
		}
	}
}

// Called when the game starts or when spawned
void AMonster::BeginPlay()
{
	Super::BeginPlay();
	CollisionComponent->SetCollisionProfileName(CollisionProfileName::Monster);
	CollisionComponent->bHiddenInGame = false;

	SetData(DataTableRowHandle, MonsterName);
}



void AMonster::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	SetData(DataTableRowHandle, MonsterName);
	SetActorTransform(Transform);
}



// Called every frame
void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TickMovement(DeltaTime);
}

float AMonster::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (StatusComponent->IsDie()) { return 0.f; }

	float DamageResult = StatusComponent->TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	if (FMath::IsNearlyZero(DamageResult)) { return 0.0; }

	if (Controller)
	{
		Controller->StopMovement();
	}



	if (StatusComponent->IsDie() && MonsterData->DieMontage)
	{
		if (Controller)
		{
			Controller->Destroy();
		}
		SetActorEnableCollision(false);

		PlayDieMontage();
		UKismetSystemLibrary::K2_SetTimer(this, TEXT("OnDie"),
			MonsterData->DieMontage->GetPlayLength() - 0.1f, false);
	}
	else if (!StatusComponent->IsDie() && MonsterData->DamageMontage)
	{
		PlayDamageMontage();
	}

	return 0.0f;
}



void AMonster::OnDie()
{
	// @TODO : Die Effect
	Destroy();
}

void AMonster::PlayAttackMontage()
{
	UAnimInstance* AnimInstance = SkeletalMeshComponent->GetAnimInstance();
	if (!AnimInstance->Montage_IsPlaying(nullptr))
	{
		AnimInstance->Montage_Play(MonsterData->AttackMontage);
	}
}

void AMonster::PlayDieMontage()
{
	UAnimInstance* AnimInstance = SkeletalMeshComponent->GetAnimInstance();
	AnimInstance->Montage_Play(MonsterData->DieMontage);
}
void AMonster::PlayDamageMontage()
{
	UAnimInstance* AnimInstance = SkeletalMeshComponent->GetAnimInstance();
	if (!AnimInstance->Montage_IsPlaying(MonsterData->DamageMontage))
	{
		AnimInstance->Montage_Play(MonsterData->DamageMontage);
	}
}
void AMonster::PlayRushMontage()
{
	UAnimInstance* AnimInstance = SkeletalMeshComponent->GetAnimInstance();
	if (!AnimInstance->Montage_IsPlaying(MonsterData->RushMontage))
	{
		AnimInstance->Montage_Play(MonsterData->RushMontage);
	}
}

bool AMonster::IsAttackMontage()
{
	return MonsterData->AttackMontage ? true : false;
}
bool AMonster::IsDieMontage()
{
	return MonsterData->DieMontage ? true : false;
}
bool AMonster::IsDamageMontage()
{
	return MonsterData->DamageMontage ? true : false;
}
bool AMonster::IsRushMontage()
{
	return MonsterData->RushMontage ? true : false;
}


bool AMonster::IsPlayingMontage()
{
	UAnimInstance* AnimInstance = SkeletalMeshComponent->GetAnimInstance();
	return AnimInstance->Montage_IsPlaying(nullptr);
}

bool AMonster::IsPlayingAttackMontage()
{
	UAnimInstance* AnimInstance = SkeletalMeshComponent->GetAnimInstance();
	return AnimInstance->Montage_IsPlaying(MonsterData->AttackMontage);
}

bool AMonster::IsPlayingDieMontage()
{
	UAnimInstance* AnimInstance = SkeletalMeshComponent->GetAnimInstance();
	return AnimInstance->Montage_IsPlaying(MonsterData->DieMontage);
}

bool AMonster::IsPlayingDamageMontage()
{
	UAnimInstance* AnimInstance = SkeletalMeshComponent->GetAnimInstance();
	return AnimInstance->Montage_IsPlaying(MonsterData->DamageMontage);
}

bool AMonster::IsPlayingRushMontage()
{
	UAnimInstance* AnimInstance = SkeletalMeshComponent->GetAnimInstance();
	return AnimInstance->Montage_IsPlaying(MonsterData->RushMontage);
}

void AMonster::TickMovement(float fDeltaTime)
{
	if (IsRushMontage() && IsPlayingRushMontage())
	{
		MovementComponent->MaxSpeed = MonsterData->RushMovementMaxSpeed;
	}
	else
	{
		MovementComponent->MaxSpeed = MonsterData->MovementMaxSpeed;   
	}

	const float Speed = UKismetMathLibrary::VSizeXY(MovementComponent->Velocity);
	if (!FMath::IsNearlyZero(Speed))
	{
		StatusComponent->SetOnAnimationStatus(MONSTER_BIT_WALK);
	}
	else
	{
		StatusComponent->SetOffAnimationStatus(MONSTER_BIT_WALK);
	}


}
