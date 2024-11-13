// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/NPC/Fish.h"
#include "Misc/Utils.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Animation/FishAnimInstance.h"
#include "Components/AdvancedFloatingPawnMovement.h"
#include "Components/SphereComponent.h"
#include "Components/StatusComponent/FishStatusComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Actors/AI/NPC/FishAIController.h"
#include "Actors/AI/PatrolPath.h"
#include "Data/FishTableRow.h"

AFish::AFish(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	FishName = NPC_Name_Korean::Fish;

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	PrimaryActorTick.bCanEverTick = true;

	MovementComponent = CreateDefaultSubobject<UAdvancedFloatingPawnMovement>(TEXT("MovementComponent"));

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	CollisionComponent->SetCollisionProfileName(CollisionProfileName::NPC);
	CollisionComponent->SetCanEverAffectNavigation(false);
	RootComponent = CollisionComponent;

	SenseLureCollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SenseLureCollisionComponent"));
	SenseLureCollisionComponent->SetCollisionProfileName(CollisionProfileName::SenseInteractive);
	SenseLureCollisionComponent->SetCanEverAffectNavigation(false);
	SenseLureCollisionComponent->SetupAttachment(RootComponent);

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	SkeletalMeshComponent->SetupAttachment(RootComponent);
	FRotator NewRotator = FRotator(0.0, 0.0, 0.0);
	SkeletalMeshComponent->SetWorldRotation(NewRotator.Quaternion());
	SkeletalMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));
	AISenseConfig_Sight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("AISenseConfig_Sight"));
	AISenseConfig_Sight->DetectionByAffiliation.bDetectNeutrals = true;
	AISenseConfig_Sight->SightRadius = FISH_AISENSECONFIG_SIGHT_SIGHTRADIUS;
	AISenseConfig_Sight->LoseSightRadius = FISH_AISENSECONFIG_SIGHT_LOSESIGHTRADIUS;
	AISenseConfig_Sight->PeripheralVisionAngleDegrees = FISH_AISENSECONFIG_SIGHT_LOSESIGHTRADIUS_PERIPHERALVISIONANGLEDEGREES;
	AIPerceptionComponent->ConfigureSense(*AISenseConfig_Sight);

	StatusComponent = CreateDefaultSubobject<UFishStatusComponent>(TEXT("StatusComponent"));
}

void AFish::SetData(const FDataTableRowHandle& InDataTableRowHandle)
{
	DataTableRowHandle = InDataTableRowHandle;
	if (DataTableRowHandle.IsNull()) { return; }
	FFishTableRow* Data = DataTableRowHandle.GetRow<FFishTableRow>(DataTableRowHandle.RowName.ToString());
	if (!Data) { return; }
	FishData = Data;

	if (IsValid(CollisionComponent))
	{
		USphereComponent* SphereComponent = Cast<USphereComponent>(CollisionComponent);
		SphereComponent->SetSphereRadius(FishData->CollisionSphereRadius);
		CollisionComponent->SetCollisionProfileName(CollisionProfileName::NPC);
		CollisionComponent->bHiddenInGame = COLLISION_HIDDEN_IN_GAME;
		CollisionComponent->RegisterComponent();
	}

	if (IsValid(SenseLureCollisionComponent))
	{
		USphereComponent* SphereComponent = Cast<USphereComponent>(SenseLureCollisionComponent);
		SphereComponent->SetSphereRadius(FishData->SenseLureCollisionSphereRadius);
		SenseLureCollisionComponent->SetCollisionProfileName(CollisionProfileName::SenseInteractive);
		SenseLureCollisionComponent->bHiddenInGame = COLLISION_HIDDEN_IN_GAME;
		SenseLureCollisionComponent->RegisterComponent();
	}

	SkeletalMeshComponent->SetSkeletalMesh(FishData->SkeletalMesh);
	SkeletalMeshComponent->SetAnimClass(FishData->AnimClass);
	SkeletalMeshComponent->SetRelativeTransform(FishData->MeshTransform);
	MovementComponent->MaxSpeed = FishData->MovementMaxSpeed;

	AIControllerClass = FishData->AIControllerClass;
}

void AFish::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFish::PostDuplicate(EDuplicateMode::Type DuplicateMode)
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

void AFish::PostLoad()
{
	Super::PostLoad();
}

void AFish::PostLoadSubobjects(FObjectInstancingGraph* OuterInstanceGraph)
{
	Super::PostLoadSubobjects(OuterInstanceGraph);
}

void AFish::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (PatrolPathRef)
	{
		if (AFishAIController* FishAIController = Cast<AFishAIController>(Controller))
		{
			FishAIController->SetPatrolPath(PatrolPathRef->GetPath());
		}
	}
}

void AFish::BeginPlay()
{
	Super::BeginPlay();
}

void AFish::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	SetActorTransform(Transform);
	SetData(DataTableRowHandle);
}

TObjectPtr<UAdvancedFloatingPawnMovement> AFish::GetMovementComponent()
{
	return MovementComponent;
}

void AFish::SetCollisionProfileName(FName CollisionProfile)
{
	CollisionComponent->SetCollisionProfileName(CollisionProfile);
}

void AFish::PlayMontage(FISH_MONTAGE _InEnum, bool bIsLoop)
{
	UAnimInstance* AnimInstance = SkeletalMeshComponent->GetAnimInstance();

	UAnimMontage* tempMontage = nullptr;
	// NPC_MONTAGE

	switch (_InEnum
)
	{
	case FISH_MONTAGE::POKE:
		tempMontage = FishData->PokeMontage;
		break;
	case FISH_MONTAGE::TURN:
		tempMontage = FishData->TurnMontage;
		break;
	case FISH_MONTAGE::END:
		break;
	default:
		break;
	}

	if (tempMontage/* && !AnimInstance->Montage_IsPlaying(tempMontage)*/)
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

bool AFish::IsMontage(FISH_MONTAGE _InEnum)
{
	if (!FishData) return false;

	switch (_InEnum)
	{
	case FISH_MONTAGE::POKE:
		return FishData->PokeMontage ? true : false;
	case FISH_MONTAGE::TURN:
		return FishData->TurnMontage ? true : false;
	default:
		return false;
	}
}

bool AFish::IsPlayingMontage(FISH_MONTAGE _InEnum)
{
	if (!FishData) return false;
	UAnimInstance* AnimInstance = SkeletalMeshComponent->GetAnimInstance();

	switch (_InEnum)
	{
	case FISH_MONTAGE::POKE:
		return AnimInstance->Montage_IsPlaying(FishData->PokeMontage);
	case FISH_MONTAGE::TURN:
		return AnimInstance->Montage_IsPlaying(FishData->TurnMontage);
	default:
		return false;
	}
}
