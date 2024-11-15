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
#include "GameFramework/Character.h"

#define FISH_X_MAX			50.f
#define FISH_X_MIN			-1620.f
#define FISH_Y_MAX			160.f	
#define FISH_Y_MIN			-420.f
#define FISH_Z_MAX			700.f
#define FISH_Z_MIN			80.f

AFish::AFish(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	PrimaryActorTick.bCanEverTick = true;

	//MovementComponent = CreateDefaultSubobject<UAdvancedFloatingPawnMovement>(TEXT("MovementComponent"));
	//MovementComponent->SetIsGravity(false);


	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	CollisionComponent->SetCollisionProfileName(CollisionProfileName::Fish);
	CollisionComponent->SetCanEverAffectNavigation(false);
	CollisionComponent->bHiddenInGame = COLLISION_HIDDEN_IN_GAME;
	RootComponent = CollisionComponent;


	CollisionComponent->SetPhysMaterialOverride(PhysicalMaterial);
	CollisionComponent->SetEnableGravity(false);
	CollisionComponent->SetSimulatePhysics(true);
	CollisionComponent->SetLinearDamping(0.8f);


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
	AISenseConfig_Sight->PeripheralVisionAngleDegrees = FISH_AISENSECONFIG_SIGHT_PERIPHERALVISIONANGLEDEGREES;
	AIPerceptionComponent->ConfigureSense(*AISenseConfig_Sight);

	StatusComponent = CreateDefaultSubobject<UFishStatusComponent>(TEXT("StatusComponent"));

	static ConstructorHelpers::FObjectFinder<UPhysicalMaterial> PhysMaterial(TEXT("/Script/PhysicsCore.PhysicalMaterial'/Game/Blueprint/NPC/FishingLure/PM_Fish.PM_Fish'"));
	PhysicalMaterial = PhysMaterial.Object;

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
		//CollisionComponent->RegisterComponent();
	}

	SkeletalMeshComponent->SetSkeletalMesh(FishData->SkeletalMesh);
	SkeletalMeshComponent->SetAnimClass(FishData->AnimClass);
	SkeletalMeshComponent->SetRelativeTransform(FishData->MeshTransform);
	//MovementComponent->MaxSpeed = FishData->MovementMaxSpeed;

	AIControllerClass = FishData->AIControllerClass;
}

void AFish::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const FISH_STATUS eFishStatus = StatusComponent->GetFishStatus();
	if (FISH_STATUS::CATCHED != eFishStatus)
	{

		if (FISH_STATUS::FIGHTING != eFishStatus)
		{
			FVector GetCurrentLocation = GetActorLocation();
			GetCurrentLocation.X = FMath::Clamp(GetCurrentLocation.X, FISH_X_MIN, FISH_X_MAX);
			GetCurrentLocation.Y = FMath::Clamp(GetCurrentLocation.Y, FISH_Y_MIN, FISH_Y_MAX);
			GetCurrentLocation.Z = FMath::Clamp(GetCurrentLocation.Z, FISH_Z_MIN, FISH_Z_MAX);
			SetActorLocation(GetCurrentLocation);
		}
		//else
		//{
		//	ACharacter* Character = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
		//	if (Character)
		//	{
		//		DesiredDirection = Character->GetActorLocation() - GetActorLocation();
		//		DesiredDirection.Normalize();
		//	}
		//}
		FVector GoalDirection = FMath::Lerp(GetActorForwardVector(), DesiredDirection, 0.2f);

		SetActorRotation(GoalDirection.Rotation().Quaternion());
	}


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
	SetData(DataTableRowHandle);
	CollisionComponent->SetCollisionProfileName(CollisionProfileName::Fish);
}

void AFish::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	SetActorTransform(Transform);
	SetData(DataTableRowHandle);
}

//TObjectPtr<UAdvancedFloatingPawnMovement> AFish::GetMovementComponent()
//{
//	return MovementComponent;
//}

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

void AFish::AddForce(FVector Direction)
{
	if (CollisionComponent)
	{
		CollisionComponent->AddForce(Direction);
	}
}

void AFish::SetPhysicsLinearVelocity(FVector _Velocity)
{
	if (CollisionComponent)
	{
		CollisionComponent->SetPhysicsLinearVelocity(_Velocity);
	}
}
