// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Link.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/SoftWheelSpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SoftWheelSpringArmComponent.h"
#include "Components/LinkStatusComponent.h"
#include "Actors/Projectile/ProjectileTableRow.h"
#include "Components/SphereComponent.h"
#include "Misc/Utils.h"
#include "Actors/Monsters/Hinox.h"


#define PROBE_SIZE					5.0

#define LINK_WALK_SPEED				100.f
#define LINK_RUN_SPEED				300.f

// Sets default values
ALink::ALink(const FObjectInitializer& ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	UCapsuleComponent* tempCapsuleComponent = GetCapsuleComponent();
	tempCapsuleComponent->SetCanEverAffectNavigation(false);
	RootComponent = tempCapsuleComponent;
	tempCapsuleComponent->SetCollisionProfileName(CollisionProfileName::Link);

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
		Movement->MaxWalkSpeed = LINK_WALK_SPEED;
		Movement->bCanWalkOffLedges = false;
	}


	USkeletalMeshComponent* SkeletalMeshComponent = GetMesh();
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	SkeletalMeshComponent->SetupAttachment(RootComponent);
	//SkeletalMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	//GetCapsuleComponent()->SetCollisionObjectType(COLLISION_CHANNEL_LINK);
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
	tempCapsuleComponent->bHiddenInGame = false;
	//tempCapsuleComponent->SetGenerateOverlapEvents(true);
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
