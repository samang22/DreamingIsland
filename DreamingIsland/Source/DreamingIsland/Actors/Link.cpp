// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Link.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/SoftWheelSpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SoftWheelSpringArmComponent.h"
#include "Components/LinkStatusComponent.h"


#define PROBE_SIZE					5.0
#define MIN_TARGET_ARM_LENGTH		200.f

#define LINK_WALK_SPEED				100.f
#define LINK_RUN_SPEED				300.f

// Sets default values
ALink::ALink(const FObjectInitializer& ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	//GetCapsuleComponent()->SetCollisionProfileName(CollisionProfileName::Player);
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
		//Movement->RotationRate = CharacterData->RotationRate;
		Movement->bOrientRotationToMovement = true;
		//Movement->GetNavAgentPropertiesRef().bCanCrouch = true;
		Movement->MaxWalkSpeed = LINK_WALK_SPEED;
		//Movement->SetCrouchedHalfHeight(NewCapsuleHalfHeight);
		Movement->bCanWalkOffLedges = false;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> MtgAsset(TEXT("/Script/Engine.AnimMontage'/Game/Assets/Link/Animation/MTG_Slash.MTG_Slash'"));
	check(MtgAsset.Object);
	AttackMontage = MtgAsset.Object;	
}

void ALink::OnDie()
{
}

// Called when the game starts or when spawned
void ALink::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALink::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

// Called every frame
void ALink::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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

