// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Monsters/Monster.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Misc/Utils.h"
#include "Data/PawnTableRow.h"
#include "GameFramework/Character.h"
#include "Animation/MonsterAnimInstance.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Components/AdvancedFloatingPawnMovement.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WeaponChildActorComponent.h"
#include "Components/StatusComponent/MonsterStatusComponent.h"
#include "Components/StatusComponent/MoblinStatusComponent.h"
#include "Actors/AI/PatrolPath.h"
#include "Actors/AI/Monsters/BasicMonsterAIController.h"
#include "Actors/AI/Monsters/RangedMonsterAIController.h"
#include "Actors/AI/Monsters/MoblinAIController.h"
#include "Actors/AI/Monsters/MoriblinAIController.h"
#include "Actors/AI/Monsters/HinoxAIController.h"
#include "Actors/AI/Monsters/BomberAIController.h"
#include "Actors/Weapon/Weapon.h"

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

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	CollisionComponent->SetCollisionProfileName(CollisionProfileName::Monster);

	CollisionComponent->SetCanEverAffectNavigation(false);
	RootComponent = CollisionComponent;

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	SkeletalMeshComponent->SetupAttachment(RootComponent);
	FRotator NewRotator = FRotator(0.0, 0.0, 0.0);
	SkeletalMeshComponent->SetWorldRotation(NewRotator.Quaternion());

	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));
	AISenseConfig_Sight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("AISenseConfig_Sight"));
	AISenseConfig_Sight->DetectionByAffiliation.bDetectNeutrals = true;
	AISenseConfig_Sight->SightRadius = AISENSECONFIG_SIGHT_SIGHTRADIUS;
	AISenseConfig_Sight->LoseSightRadius = AISENSECONFIG_SIGHT_LOSESIGHTRADIUS;
	AISenseConfig_Sight->PeripheralVisionAngleDegrees = AISENSECONFIG_SIGHT_LOSESIGHTRADIUS_PERIPHERALVISIONANGLEDEGREES;
	AIPerceptionComponent->ConfigureSense(*AISenseConfig_Sight);

	Weapon = nullptr;

	StatusComponent = CreateDefaultSubobject<UMonsterStatusComponent>(TEXT("StatusComponent"));
	Weapon = CreateDefaultSubobject<UWeaponChildActorComponent>(TEXT("Weapon"));
	Weapon->SetupAttachment(SkeletalMeshComponent, Monster_SocketName::Weapon);


}

void AMonster::SetData(const FDataTableRowHandle& InDataTableRowHandle)
{
	DataTableRowHandle = InDataTableRowHandle;
	if (DataTableRowHandle.IsNull()) { return; }
	FPawnTableRow* Data = DataTableRowHandle.GetRow<FPawnTableRow>(DataTableRowHandle.RowName.ToString());
	if (!Data) { return; }
	MonsterData = Data;

	if (IsValid(CollisionComponent))
	{
		USphereComponent* SphereComponent = Cast<USphereComponent>(CollisionComponent);
		SphereComponent->SetSphereRadius(MonsterData->CollisionSphereRadius);
		CollisionComponent->SetCollisionProfileName(CollisionProfileName::Monster);
		CollisionComponent->bHiddenInGame = COLLISION_HIDDEN_IN_GAME;
		CollisionComponent->RegisterComponent();

	}

	SkeletalMeshComponent->SetSkeletalMesh(MonsterData->SkeletalMesh);
	SkeletalMeshComponent->SetAnimClass(MonsterData->AnimClass);
	SkeletalMeshComponent->SetRelativeTransform(MonsterData->MeshTransform);
	MovementComponent->MaxSpeed = MonsterData->MovementMaxSpeed;

	AIControllerClass = MonsterData->AIControllerClass;

	if (MonsterData->bUseWeapon)
	{
		Weapon->SetData(MonsterData->WeaponTableRowHandle);
	}
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
		SetData(DataTableRowHandle);
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
		else if (ARangedMonsterAIController* RangedMonsterAIController = Cast<ARangedMonsterAIController>(Controller))
		{
			RangedMonsterAIController->SetPatrolPath(PatrolPathRef->GetPath());
		}
		else if (AMoblinAIController* MoblinAIController = Cast<AMoblinAIController>(Controller))
		{
			MoblinAIController->SetPatrolPath(PatrolPathRef->GetPath());
		}
		else if (AMoriblinAIController* MoriblinAIController = Cast<AMoriblinAIController>(Controller))
		{
			MoriblinAIController->SetPatrolPath(PatrolPathRef->GetPath());
		}
		else if (AHinoxAIController* HinoxAIController = Cast<AHinoxAIController>(Controller))
		{
			HinoxAIController->SetPatrolPath(PatrolPathRef->GetPath());
		}
		else if (ABomberAIController* BomberAIController = Cast<ABomberAIController>(Controller))
		{
			BomberAIController->SetPatrolPath(PatrolPathRef->GetPath());
		}
		else
		{
			check(false);
		}
	}
}

// Called when the game starts or when spawned
void AMonster::BeginPlay()
{
	Super::BeginPlay();
	CollisionComponent->SetCollisionProfileName(CollisionProfileName::Monster);
	CollisionComponent->bHiddenInGame = COLLISION_HIDDEN_IN_GAME;
	SetData(DataTableRowHandle);
	if (MonsterData && MonsterData->bUseWeapon)
	{
		RenderOnWeapon();
		SetWeaponEquiped();
	}
}



void AMonster::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	SetData(DataTableRowHandle);
	SetActorTransform(Transform);
}



// Called every frame
void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TickMovement(DeltaTime);
}

void AMonster::PlayMontage(MONSTER_MONTAGE _InEnum, bool bIsLoop)
{
	UAnimInstance* AnimInstance = SkeletalMeshComponent->GetAnimInstance();

	UAnimMontage* tempMontage = nullptr;
	switch (_InEnum)
	{
	case MONSTER_MONTAGE::ATTACK:
		tempMontage = MonsterData->AttackMontage;
		break;
	case MONSTER_MONTAGE::DEAD:
		tempMontage = MonsterData->DeadMontage;
		break;
	case MONSTER_MONTAGE::DAMAGE:
		tempMontage = MonsterData->DamageMontage;
		break;
	case MONSTER_MONTAGE::RUSH:
		tempMontage = MonsterData->RushMontage;
		break;
	case MONSTER_MONTAGE::FIND:
		tempMontage = MonsterData->FindMontage;
		break;
	case MONSTER_MONTAGE::KYOROKYORO:
		tempMontage = MonsterData->KyoroKyoroMontage;
		break;
	case MONSTER_MONTAGE::GUARD:
		tempMontage = MonsterData->GuardMontage;
		break;
	case MONSTER_MONTAGE::LAUGH:
		tempMontage = MonsterData->LaughMontage;
		break;
	case MONSTER_MONTAGE::CATCH_NO:
		tempMontage = MonsterData->CatchNoMontage;
		break;
	case MONSTER_MONTAGE::THROW:
		tempMontage = MonsterData->ThrowMontage;
		break;
	default:
		break;
	}

	if (tempMontage && !AnimInstance->Montage_IsPlaying(tempMontage))
	{
		if (bIsLoop)
		{
			AnimInstance->Montage_Play(tempMontage, 1.0f, EMontagePlayReturnType::MontageLength, 0.0f, true);
		}
		else
		{
			AnimInstance->Montage_Play(tempMontage);
		}
	}
}
bool AMonster::IsMontage(MONSTER_MONTAGE _InEnum)
{
	switch (_InEnum)
	{
	case MONSTER_MONTAGE::ATTACK:
		if (!MonsterData) return false;
		return MonsterData->AttackMontage ? true : false;
	case MONSTER_MONTAGE::DEAD:
		if (!MonsterData) return false;
		return MonsterData->DeadMontage ? true : false;
	case MONSTER_MONTAGE::DAMAGE:
		if (!MonsterData) return false;
		return MonsterData->DamageMontage ? true : false;
	case MONSTER_MONTAGE::RUSH:
		if (!MonsterData) return false;
		return MonsterData->RushMontage ? true : false;
	case MONSTER_MONTAGE::FIND:
		if (!MonsterData) return false;
		return MonsterData->FindMontage ? true : false;
	case MONSTER_MONTAGE::KYOROKYORO:
		if (!MonsterData) return false;
		return MonsterData->KyoroKyoroMontage ? true : false;
	case MONSTER_MONTAGE::GUARD:
		if (!MonsterData) return false;
		return MonsterData->GuardMontage ? true : false;
	case MONSTER_MONTAGE::LAUGH:
		if (!MonsterData) return false;
		return MonsterData->LaughMontage ? true : false;
	case MONSTER_MONTAGE::CATCH_NO:
		if (!MonsterData) return false;
		return MonsterData->CatchNoMontage ? true : false;
	case MONSTER_MONTAGE::THROW:
		if (!MonsterData) return false;
		return MonsterData->ThrowMontage ? true : false;
	default:
		return false;
	}
}
bool AMonster::IsPlayingMontage(MONSTER_MONTAGE _InEnum)
{
	if (!MonsterData) return false;
	UAnimInstance* AnimInstance = SkeletalMeshComponent->GetAnimInstance();

	switch (_InEnum)
	{
	case MONSTER_MONTAGE::ATTACK:
		return AnimInstance->Montage_IsPlaying(MonsterData->AttackMontage);
	case MONSTER_MONTAGE::DEAD:
		return AnimInstance->Montage_IsPlaying(MonsterData->DeadMontage);
	case MONSTER_MONTAGE::DAMAGE:
		return AnimInstance->Montage_IsPlaying(MonsterData->DamageMontage);
	case MONSTER_MONTAGE::RUSH:
		return AnimInstance->Montage_IsPlaying(MonsterData->RushMontage);
	case MONSTER_MONTAGE::FIND:
		return AnimInstance->Montage_IsPlaying(MonsterData->FindMontage);
	case MONSTER_MONTAGE::KYOROKYORO:
		return AnimInstance->Montage_IsPlaying(MonsterData->KyoroKyoroMontage);
	case MONSTER_MONTAGE::GUARD:
		return AnimInstance->Montage_IsPlaying(MonsterData->GuardMontage);
	case MONSTER_MONTAGE::LAUGH:
		return AnimInstance->Montage_IsPlaying(MonsterData->LaughMontage);
	case MONSTER_MONTAGE::CATCH_NO:
		return AnimInstance->Montage_IsPlaying(MonsterData->CatchNoMontage);
	case MONSTER_MONTAGE::THROW:
		return AnimInstance->Montage_IsPlaying(MonsterData->ThrowMontage);
	default:
		return AnimInstance->Montage_IsPlaying(nullptr);
	}

	return AnimInstance->Montage_IsPlaying(nullptr);
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



	if (StatusComponent->IsDie() && MonsterData->DeadMontage)
	{
		if (Controller)
		{
			Controller->Destroy();
		}
		SetActorEnableCollision(false);

		PlayMontage(MONSTER_MONTAGE::DEAD);
		UKismetSystemLibrary::K2_SetTimer(this, TEXT("OnDie"), MonsterData->DeadMontage->GetPlayLength() - 0.1f, false);
	}
	else if (!StatusComponent->IsDie() && MonsterData->DamageMontage)
	{
		PlayMontage(MONSTER_MONTAGE::DAMAGE);
	}

	return 0.0f;
}



void AMonster::OnDie()
{
	// @TODO : Die Effect
	Destroy();
}

void AMonster::TickMovement(float fDeltaTime)
{
	if (!MonsterData) return;

	if (IsMontage(MONSTER_MONTAGE::RUSH) && IsPlayingMontage(MONSTER_MONTAGE::RUSH))
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
bool AMonster::GetIsWeaponEquiped()
{
	return bIsWeaponEquiped;
}
void AMonster::SetWeaponEquiped()
{
	bIsWeaponEquiped = true;
}
void AMonster::SetWeaponUnEquiped()
{
	bIsWeaponEquiped = false;
	StatusComponent->SetHoldingWeaponOff();
}

void AMonster::RenderOffWeapon()
{
	Weapon->RenderOff();
	StatusComponent->SetHoldingWeaponOn();
}
void AMonster::RenderOnWeapon()
{
	Weapon->RenderOn();
}

FVector AMonster::GetSocketLocation(FName SocketName)
{
	return SkeletalMeshComponent->GetSocketLocation(SocketName);
}

void AMonster::SetCollisionProfileName(FName CollisionProfile)
{
	CollisionComponent->SetCollisionProfileName(CollisionProfile);
}
