// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Link/Link.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/SoftWheelSpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SoftWheelSpringArmComponent.h"
#include "Components/StatusComponent/LinkStatusComponent.h"
#include "Actors/Projectile/ProjectileTableRow.h"
#include "Components/SphereComponent.h"
#include "Misc/Utils.h"
#include "Actors/Monsters/Hinox.h"
#include "Actors/NPC/NPC.h"
#include "Actors/Items/Item.h"
#include "Actors/Link/LinkController.h"
#include "Animation/LinkAnimInstance.h"

#define PROBE_SIZE										5.0
#define COLLISION_SPHERE_RADIUS							24.f
#define LINK_WALK_SPEED									500.f
#define LINK_RUN_SPEED									1000.f
#define LINK_SENSEINTERACTIVE_COLLISION_SPHERE_RADIUS	48.f
#define LINK_SENSE_COLLISION_OFFSET						48.f
#define LINK_CAPSULE_HALF_HEIGHT						200.f

// Sets default values
ALink::ALink(const FObjectInitializer& ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	UCapsuleComponent* tempCapsuleComponent = GetCapsuleComponent();
	tempCapsuleComponent->SetCanEverAffectNavigation(false);
	RootComponent = tempCapsuleComponent;
	tempCapsuleComponent->SetCollisionProfileName(CollisionProfileName::Link);
	tempCapsuleComponent->SetCapsuleHalfHeight(LINK_CAPSULE_HALF_HEIGHT);


	SenseInteractCollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SenseInteractCollisionComponent"));
	SenseInteractCollisionComponent->SetCanEverAffectNavigation(false);
	SenseInteractCollisionComponent->bHiddenInGame = COLLISION_HIDDEN_IN_GAME;
	SenseInteractCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnSenseInteractiveBeginOverlap);
	SenseInteractCollisionComponent->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnSenseInteractiveEndOverlap);
	SenseInteractCollisionComponent->SetupAttachment(RootComponent);
	SenseInteractCollisionComponent->SetRelativeLocation(GetActorForwardVector() * LINK_SENSE_COLLISION_OFFSET);
	SenseInteractCollisionComponent->SetSphereRadius(LINK_SENSEINTERACTIVE_COLLISION_SPHERE_RADIUS);
	SenseInteractCollisionComponent->SetCollisionProfileName(CollisionProfileName::SenseInteractive);

	SpringArm = CreateDefaultSubobject<USoftWheelSpringArmComponent>(TEXT("SpringArm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	{
		SpringArm->SetupAttachment(GetMesh());
		SpringArm->ProbeSize = PROBE_SIZE;
		SpringArm->bUsePawnControlRotation = true;
		SpringArm->bInheritRoll = false;
		SpringArm->SetMinMaxTargetArmLength(MIN_TARGET_ARM_LENGTH, SpringArm->GetMaxTargetArmLength());
	}
	Camera->SetupAttachment(SpringArm);

	bUseControllerRotationYaw = false;

	const FRotator Rotation = FRotator(0., 0., 0.);
	const FVector Translation = FVector(0., 0., 90.0);
	FTransform SpringArmTransform = FTransform(Rotation, Translation, FVector::OneVector);
	SpringArm->SetRelativeTransform(SpringArmTransform);

	StatusComponent = CreateDefaultSubobject<ULinkStatusComponent>(TEXT("StatusComponent"));

	{
		UCharacterMovementComponent* Movement = GetCharacterMovement();
		Movement->bOrientRotationToMovement = true;
		Movement->RotationRate = FRotator(0.f, 720.0f, 0.0f);
		Movement->MaxWalkSpeed = LINK_WALK_SPEED;
		Movement->bCanWalkOffLedges = false;
	}


	USkeletalMeshComponent* SkeletalMeshComponent = GetMesh();
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	SkeletalMeshComponent->SetupAttachment(RootComponent);



}



void ALink::OnDie()
{
}

// Called when the game starts or when spawned
void ALink::BeginPlay()
{
	Super::BeginPlay();
	UCapsuleComponent* tempCapsuleComponent = GetCapsuleComponent();
	tempCapsuleComponent->SetCollisionProfileName(CollisionProfileName::Link);
	tempCapsuleComponent->bHiddenInGame = COLLISION_HIDDEN_IN_GAME;
	tempCapsuleComponent->SetCollisionResponseToChannel(TRACE_CHANNEL_LINKCHANNEL, ECR_Block);

	SenseInteractCollisionComponent->SetRelativeLocation(GetActorForwardVector() * LINK_SENSE_COLLISION_OFFSET);
	SenseInteractCollisionComponent->SetSphereRadius(LINK_SENSEINTERACTIVE_COLLISION_SPHERE_RADIUS);
	SenseInteractCollisionComponent->SetCollisionProfileName(CollisionProfileName::SenseInteractive);

	ALinkController* LinkController = Cast<ALinkController>(Controller);
	LinkController->OnLinkTalk.AddDynamic(this, &ThisClass::OnLinkTalk);
	LinkController->OnLinkTalkEnd.AddDynamic(this, &ThisClass::OnLinkTalkEnd);

}

void ALink::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

// Called every frame
void ALink::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	LinkCatchedSequence(DeltaTime);
}

// Called to bind functionality to input
void ALink::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float ALink::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	return 0.0f;
}

void ALink::OnSenseInteractiveBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ANPC* NPC = Cast<ANPC>(OtherActor);
	if (NPC)
	{
		OverlappedNPC = NPC;
		return;
	}

	AItem* Item = Cast<AItem>(OtherActor);
	if (Item)
	{
		OverlappedItem = Item;
	}
}

void ALink::OnSenseInteractiveEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor == OverlappedNPC)
	{
		OverlappedNPC = nullptr;
	}
	else if (OtherActor == OverlappedItem)
	{
		OverlappedItem = nullptr;
	}
}

void ALink::SetSpeedWalk()
{
	UCharacterMovementComponent* Movement = GetCharacterMovement();
	Movement->MaxWalkSpeed = LINK_WALK_SPEED;
}

void ALink::SetSpeedRun()
{
	UCharacterMovementComponent* Movement = GetCharacterMovement();
	Movement->MaxWalkSpeed = LINK_RUN_SPEED;
}

const ULinkStatusComponent* ALink::GetStatusComponent() const
{
	return dynamic_cast<ULinkStatusComponent*>(StatusComponent);
}

void ALink::StopMovement()
{
	UCharacterMovementComponent* Movement = GetCharacterMovement();
	Movement->MaxWalkSpeed = 0.f;
}

void ALink::ResumeMovement()
{
	UCharacterMovementComponent* Movement = GetCharacterMovement();
	Movement->MaxWalkSpeed = LINK_WALK_SPEED;
}

void ALink::LinkCatchedSequence(float DeltaTime)
{
	if (bIsCatched)
	{
		if (CatchingLinkActor)
		{
			AHinox* Hinox = Cast<AHinox>(CatchingLinkActor);
			if (Hinox)
			{
				SetActorLocation(Hinox->GetSocketLocation(Monster_SocketName::Weapon));
			}
			else
			{
				// To prevent link stuck in the ground;
				FVector OffsetVector = CatchingLinkActor->GetActorLocation();
				OffsetVector.Z += 20.f;
				SetActorLocation(OffsetVector);
			}
		}
	}
}

FVector ALink::GetSocketLocation(FName SocketName)
{
	return GetMesh()->GetSocketLocation(SocketName);
}

bool ALink::IsOverlappedNPC()
{
	if (OverlappedNPC)
	{
		return true;
	}
	return false;
}

bool ALink::IsOverlappedItem()
{
	if (OverlappedItem)
	{
		return true;
	}
	return false;
}

void ALink::CatchItem()
{
	if (!OverlappedItem) return;
	AItem* Item = Cast<AItem>(OverlappedItem);
	Item->SetItemCatched(true);
	Item->SetCatchingItemActor(this);
	CatchingItem = OverlappedItem;
	OverlappedItem = nullptr;
	StatusComponent->SetOnAnimationStatus(LINK_BIT_CARRY);
}

void ALink::LayItem()
{
	if (!CatchingItem) return;
	AItem* Item = Cast<AItem>(CatchingItem);
	if (Item)
	{
		Item->SetItemCatched(false);
		Item->SetCatchingItemActor(nullptr);
	}
	CatchingItem = nullptr;
	StatusComponent->SetOffAnimationStatus(LINK_BIT_CARRY);
}

bool ALink::IsCatchingItem()
{
	if (CatchingItem)
	{
		return true;
	}
	return false;
}

void ALink::PlayMontage(LINK_MONTAGE _InEnum, bool bIsLoop)
{
	ULinkAnimInstance* LinkAnimInstance = Cast<ULinkAnimInstance>(GetMesh()->GetAnimInstance());
	LinkAnimInstance->PlayMontage(_InEnum, bIsLoop);
}

bool ALink::IsMontage(LINK_MONTAGE _InEnum)
{
	ULinkAnimInstance* LinkAnimInstance = Cast<ULinkAnimInstance>(GetMesh()->GetAnimInstance());
	return LinkAnimInstance->IsMontage(_InEnum);
}

bool ALink::IsPlayingMontage(LINK_MONTAGE _InEnum)
{
	ULinkAnimInstance* LinkAnimInstance = Cast<ULinkAnimInstance>(GetMesh()->GetAnimInstance());
	return LinkAnimInstance->IsPlayingMontage(_InEnum);
}

void ALink::SetMoveAuto(bool bFlag, FVector Direction)
{
	Cast<ALinkController>(Controller)->SetMoveAuto(bFlag, Direction);
}

void ALink::OnLinkTalk(FVector LinkLocation, FVector LinkLeftVector, FVector LinkForwardVector)
{
	if (OverlappedNPC)
	{
		ANPC* NPC = Cast<ANPC>(OverlappedNPC);
		NPC->SetIsTalking(true, GetActorLocation());
	}
}

void ALink::OnLinkTalkEnd()
{
	if (OverlappedNPC)
	{
		Cast<ANPC>(OverlappedNPC)->SetIsTalking(false, GetActorLocation());
	}
}
