// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/NPC/NPC.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Animation/NPCAnimInstance.h"
#include "Components/AdvancedFloatingPawnMovement.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/StatusComponent/NPCStatusComponent.h"
#include "Components/ConversationComponent/ConversationComponent.h"
#include "Data/NPCTableRow.h"
#include "Misc/Utils.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Actors/AI/NPC/NPCAIController.h"
#include "Actors/AI/PatrolPath.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

ANPC::ANPC(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	PrimaryActorTick.bCanEverTick = true;

	MovementComponent = CreateDefaultSubobject<UAdvancedFloatingPawnMovement>(TEXT("MovementComponent"));

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	CollisionComponent->SetCollisionProfileName(CollisionProfileName::NPC);
	CollisionComponent->SetCanEverAffectNavigation(false);
	RootComponent = CollisionComponent;

	SenseLinkCollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SenseLinkCollisionComponent"));
	SenseLinkCollisionComponent->SetCollisionProfileName(CollisionProfileName::SenseLink);
	SenseLinkCollisionComponent->SetCanEverAffectNavigation(false);
	SenseLinkCollisionComponent->SetupAttachment(RootComponent);

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	SkeletalMeshComponent->SetupAttachment(RootComponent);
	FRotator NewRotator = FRotator(0.0, 0.0, 0.0);
	SkeletalMeshComponent->SetWorldRotation(NewRotator.Quaternion());
	SkeletalMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));
	AISenseConfig_Sight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("AISenseConfig_Sight"));
	AISenseConfig_Sight->DetectionByAffiliation.bDetectNeutrals = true;
	AISenseConfig_Sight->SightRadius = NPC_AISENSECONFIG_SIGHT_SIGHTRADIUS;
	AISenseConfig_Sight->LoseSightRadius = NPC_AISENSECONFIG_SIGHT_LOSESIGHTRADIUS;
	AISenseConfig_Sight->PeripheralVisionAngleDegrees = NPC_AISENSECONFIG_SIGHT_LOSESIGHTRADIUS_PERIPHERALVISIONANGLEDEGREES;
	AIPerceptionComponent->ConfigureSense(*AISenseConfig_Sight);

	StatusComponent = CreateDefaultSubobject<UNPCStatusComponent>(TEXT("StatusComponent"));

	// Conversation Status will be Created in Subclass

}

void ANPC::SetData(const FDataTableRowHandle& InDataTableRowHandle)
{
	DataTableRowHandle = InDataTableRowHandle;
	if (DataTableRowHandle.IsNull()) { return; }
	FNPCTableRow* Data = DataTableRowHandle.GetRow<FNPCTableRow>(DataTableRowHandle.RowName.ToString());
	if (!Data) { return; }
	NPCData = Data;

	if (IsValid(CollisionComponent))
	{
		USphereComponent* SphereComponent = Cast<USphereComponent>(CollisionComponent);
		SphereComponent->SetSphereRadius(NPCData->CollisionSphereRadius);
		CollisionComponent->SetCollisionProfileName(CollisionProfileName::NPC);
		CollisionComponent->bHiddenInGame = COLLISION_HIDDEN_IN_GAME;
		CollisionComponent->RegisterComponent();
	}

	if (IsValid(SenseLinkCollisionComponent))
	{
		USphereComponent* SphereComponent = Cast<USphereComponent>(SenseLinkCollisionComponent);
		SphereComponent->SetSphereRadius(NPCData->SenseLinkCollisionSphereRadius);
		SenseLinkCollisionComponent->SetCollisionProfileName(CollisionProfileName::SenseLink);
		SenseLinkCollisionComponent->bHiddenInGame = COLLISION_HIDDEN_IN_GAME;
		SenseLinkCollisionComponent->RegisterComponent();
	}

	SkeletalMeshComponent->SetSkeletalMesh(NPCData->SkeletalMesh);
	SkeletalMeshComponent->SetAnimClass(NPCData->AnimClass);
	SkeletalMeshComponent->SetRelativeTransform(NPCData->MeshTransform);
	MovementComponent->MaxSpeed = NPCData->MovementMaxSpeed;

	AIControllerClass = NPCData->AIControllerClass;

}

void ANPC::PostDuplicate(EDuplicateMode::Type DuplicateMode)
{
	Super::PostDuplicate(DuplicateMode);

	if (DuplicateMode == EDuplicateMode::Normal)
	{
		FTransform Backup = GetActorTransform();
		CollisionComponent->DestroyComponent();
		SenseLinkCollisionComponent->DestroyComponent();
		SetData(DataTableRowHandle);
		SetActorTransform(Backup);
	}
}

void ANPC::PostLoad()
{
	Super::PostLoad();
}

void ANPC::PostLoadSubobjects(FObjectInstancingGraph* OuterInstanceGraph)
{
	Super::PostLoadSubobjects(OuterInstanceGraph);
}

void ANPC::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (PatrolPathRef)
	{
		if (ANPCAIController* NPCAIController = Cast<ANPCAIController>(Controller))
		{
			NPCAIController->SetPatrolPath(PatrolPathRef->GetPath());
		}
	}
}

// Called when the game starts or when spawned
void ANPC::BeginPlay()
{
	Super::BeginPlay();
	SetData(DataTableRowHandle);
	SkeletalMeshComponent->BoundsScale = 10.f;
}

void ANPC::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	SetActorTransform(Transform);
	SetData(DataTableRowHandle);
}

// Called every frame
void ANPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsTalking)
	{
		FRotator CurrentRotator = GetActorRotation();
		CurrentRotator = FMath::Lerp(CurrentRotator, DesiredRotator, 0.03f);
		SetActorRotation(CurrentRotator);
	}
}

void ANPC::SetCollisionProfileName(FName CollisionProfile)
{
	CollisionComponent->SetCollisionProfileName(CollisionProfile);
}

void ANPC::SetSenseLinkCollisionProfileName(FName CollisionProfile)
{
	SenseLinkCollisionComponent->SetCollisionProfileName(CollisionProfile);
}

void ANPC::PlayMontage(NPC_MONTAGE _InEnum, bool bIsLoop)
{
	UAnimInstance* AnimInstance = SkeletalMeshComponent->GetAnimInstance();

	UAnimMontage* tempMontage = nullptr;
	// NPC_MONTAGE

	switch (_InEnum)
	{
	case NPC_MONTAGE::BEAM_ST:
		tempMontage = NPCData->BeamStMontage;
		break;
	case NPC_MONTAGE::BEAM:
		tempMontage = NPCData->BeamMontage;
		break;
	case NPC_MONTAGE::RAGE:
		tempMontage = NPCData->RageMontage;
		break;
	case NPC_MONTAGE::ACTION01:
		tempMontage = NPCData->Action01_Montage;
		break;
	case NPC_MONTAGE::ACTION02:
		tempMontage = NPCData->Action02_Montage;
		break;
	case NPC_MONTAGE::END:
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

bool ANPC::IsMontage(NPC_MONTAGE _InEnum)
{
	if (!NPCData) return false;
	switch (_InEnum)
	{
	case NPC_MONTAGE::BEAM_ST:
		return NPCData->BeamStMontage ? true : false;
	case NPC_MONTAGE::BEAM:
		return NPCData->BeamMontage ? true : false;
	case NPC_MONTAGE::RAGE:
		return NPCData->RageMontage ? true : false;
	case NPC_MONTAGE::ACTION01:
		return NPCData->Action01_Montage ? true : false;
	case NPC_MONTAGE::ACTION02:
		return NPCData->Action02_Montage ? true : false;
	case NPC_MONTAGE::END:
	default:
		return false;
	}
}

bool ANPC::IsPlayingMontage(NPC_MONTAGE _InEnum)
{
	if (!NPCData) return false;
	UAnimInstance* AnimInstance = SkeletalMeshComponent->GetAnimInstance();

	switch (_InEnum)
	{
	case NPC_MONTAGE::BEAM_ST:
		return AnimInstance->Montage_IsPlaying(NPCData->BeamStMontage);
	case NPC_MONTAGE::BEAM:
		return AnimInstance->Montage_IsPlaying(NPCData->BeamMontage);
	case NPC_MONTAGE::RAGE:
		return AnimInstance->Montage_IsPlaying(NPCData->BeamMontage);
	case NPC_MONTAGE::ACTION01:
		return AnimInstance->Montage_IsPlaying(NPCData->Action01_Montage);
	case NPC_MONTAGE::ACTION02:
		return AnimInstance->Montage_IsPlaying(NPCData->Action02_Montage);
	case NPC_MONTAGE::END:
	default:
		return AnimInstance->Montage_IsPlaying(nullptr);
	}
	return AnimInstance->Montage_IsPlaying(nullptr);
}

FVector ANPC::GetSocketLocation(FName SocketName)
{
	return SkeletalMeshComponent->GetSocketLocation(SocketName);
}

void ANPC::SetIsTalking(bool _bIsTalking, FVector _LinkLocation)
{
	bIsTalking = _bIsTalking;
	LinkLocation = _LinkLocation;

	if (bIsTalking)
	{
		StatusComponent->SetOnAnimationStatus(NPC_BIT_TALK);

		FVector NewVector = _LinkLocation - GetActorLocation();
		NewVector.Z = 0.;
		NewVector.Normalize();

		float Pitch = FMath::Asin(NewVector.Z) * (180.0f / PI);
		float Yaw = FMath::Atan2(NewVector.Y, NewVector.X) * (180.0f / PI);
		DesiredRotator = FRotator(Pitch, Yaw, 0.f);
	}
	else
	{
		StatusComponent->SetOffAnimationStatus(NPC_BIT_TALK);
	}

}

void ANPC::OnConversation(FString Key)
{
	ConversationComponent->Conversation(NPCName.ToString(), Key);
}

FString ANPC::GetScript(FString Key) const
{
	return ConversationComponent->GetScript(Key);
}

