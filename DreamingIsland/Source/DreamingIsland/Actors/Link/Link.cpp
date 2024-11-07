// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Link/Link.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SoftWheelSpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SoftWheelSpringArmComponent.h"
#include "Components/StatusComponent/LinkStatusComponent.h"
#include "Components/SphereComponent.h"
#include "Actors/Projectile/ProjectileTableRow.h"
#include "Actors/Monsters/Hinox.h"
#include "Actors/NPC/NPC.h"
#include "Actors/Items/Item.h"
#include "Actors/Link/LinkController.h"
#include "Actors/NPC/Cucco.h"
#include "Misc/Utils.h"
#include "Animation/LinkAnimInstance.h"
#include "GameInstance/DreamingIsland_GIS.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"

#define PROBE_SIZE										5.0
#define COLLISION_SPHERE_RADIUS							24.f
#define LINK_WALK_SPEED									500.f
#define LINK_RUN_SPEED									1000.f
#define LINK_SENSEINTERACTIVE_COLLISION_SPHERE_RADIUS	48.f
#define LINK_SENSE_COLLISION_OFFSET						48.f
#define LINK_CAPSULE_HALF_HEIGHT						200.f

#define SLASH_EFFECT_OFFSET								10.f

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

	NiagaraComponent01 = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent01"));
	NiagaraComponent01->SetupAttachment(RootComponent); // 액터의 루트 컴포넌트에 붙임

	NiagaraComponent02 = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent02"));
	NiagaraComponent02->SetupAttachment(RootComponent); // 액터의 루트 컴포넌트에 붙임

	NiagaraComponent03 = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent03"));
	NiagaraComponent03->SetupAttachment(RootComponent); // 액터의 루트 컴포넌트에 붙임

	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> NiagaraAsset(TEXT("/Script/Niagara.NiagaraSystem'/Game/Assets/FxER_StylizedSlash/Niagara/Fantasy/NS_sm01_Fantasy_Slash_03_G.NS_sm01_Fantasy_Slash_03_G'"));
	if (NiagaraAsset.Object)
	{
		NiagaraEffect = NiagaraAsset.Object;
		NiagaraComponent01->SetAsset(NiagaraEffect);
		NiagaraComponent02->SetAsset(NiagaraEffect);
		NiagaraComponent03->SetAsset(NiagaraEffect);
	}

	FRotator CurrentRotation = NiagaraComponent01->GetRelativeRotation();
	FRotator NewRotation = FRotator(CurrentRotation.Pitch + 90.0f, CurrentRotation.Yaw + 180.f, CurrentRotation.Roll);
	NiagaraComponent01->SetRelativeRotation(NewRotation);
	NiagaraComponent01->SetRelativeLocation(GetActorForwardVector() * SLASH_EFFECT_OFFSET);
	NiagaraComponent02->SetRelativeRotation(NewRotation);
	NiagaraComponent02->SetRelativeLocation(GetActorForwardVector() * SLASH_EFFECT_OFFSET);
	NiagaraComponent03->SetRelativeRotation(NewRotation);
	NiagaraComponent03->SetRelativeLocation(GetActorForwardVector() * SLASH_EFFECT_OFFSET);
}



void ALink::OnDie()
{
}

void ALink::BeginPlay()
{
	Super::BeginPlay();
	UCapsuleComponent* tempCapsuleComponent = GetCapsuleComponent();
	tempCapsuleComponent->SetCollisionProfileName(CollisionProfileName::Link);
	tempCapsuleComponent->bHiddenInGame = COLLISION_HIDDEN_IN_GAME;
	tempCapsuleComponent->SetCollisionResponseToChannel(TRACE_CHANNEL_LINKCHANNEL, ECR_Block);

	//SenseInteractCollisionComponent->SetRelativeLocation(GetActorForwardVector() * LINK_SENSE_COLLISION_OFFSET);
	SenseInteractCollisionComponent->SetSphereRadius(LINK_SENSEINTERACTIVE_COLLISION_SPHERE_RADIUS);
	SenseInteractCollisionComponent->SetCollisionProfileName(CollisionProfileName::SenseInteractive);
	SenseInteractCollisionComponent->bHiddenInGame = COLLISION_HIDDEN_IN_GAME;

	ALinkController* LinkController = Cast<ALinkController>(Controller);
	LinkController->OnLinkTalk.AddDynamic(this, &ThisClass::OnLinkTalk);
	LinkController->OnLinkTalkEnd.AddDynamic(this, &ThisClass::OnLinkTalkEnd);


	SetDataFromGIS();

	UWorld* World = GetWorld();
	if (World)
	{
		// Get the current level name
		FString LevelName = World->GetName();
		if (LevelName.Equals(TEXT("Field")))
		{
			UDreamingIsland_GIS* Subsystem = GetGameInstance()->GetSubsystem<UDreamingIsland_GIS>();

			FVector LinkLocation = Subsystem->GetLinkFieldLocation();
			if (LinkLocation != FVector::Zero())
			{
				SetActorLocation(LinkLocation);
			}
		}
	}


	GetMesh()->BoundsScale = 10.f;

	if (NiagaraEffect)
	{
		NiagaraComponent01->Deactivate();
	}


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

void ALink::ActiveSpringArm()
{
	SpringArm->bEnableCameraLag = true;
	SpringArm->bUsePawnControlRotation = true;
}

void ALink::DeActiveSpringArm()
{
	SpringArm->bEnableCameraLag = false;
	SpringArm->bUsePawnControlRotation = false;
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

ULinkStatusComponent* ALink::GetStatusComponent() const
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

void ALink::ThrewItem()
{
	if (!CatchingItem) return;
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

void ALink::DestoryCatchingItem()
{
	if (!CatchingItem) return;
	StatusComponent->SetOffAnimationStatus(LINK_BIT_CARRY);
	CatchingItem->Destroy();
	CatchingItem = nullptr;
}

void ALink::SetOffAnimStatus(uint8 Bit)
{
	StatusComponent->SetOffAnimationStatus(Bit);
}

void ALink::CatchCucco()
{
	if (!OverlappedNPC) return;
	
	ACucco* Cucco = Cast<ACucco>(OverlappedNPC);
	Cucco->SetCatchingCuccoActor(this);
	Cucco->SetIsCatched(true);
	CatchingCucco = OverlappedNPC;
	OverlappedNPC = nullptr;
	StatusComponent->SetOnAnimationStatus(LINK_BIT_CARRY);
}

void ALink::LayCucco()
{
	if (!CatchingCucco) return;
	ACucco* Cucco = Cast<ACucco>(CatchingCucco);
	if (Cucco)
	{
		Cucco->SetIsCatched(false);
		Cucco->ClearCatchingCuccoActor();
	}
	CatchingCucco = nullptr;
	StatusComponent->SetOffAnimationStatus(LINK_BIT_CARRY);
}

void ALink::ThrewCucco()
{
	if (!CatchingCucco) return;
	CatchingCucco = nullptr;
	StatusComponent->SetOffAnimationStatus(LINK_BIT_CARRY);
}

bool ALink::IsCatchingCucco()
{
	return CatchingCucco ? true : false;
}

void ALink::SetDataFromGIS()
{
	UDreamingIsland_GIS* Subsystem = GetGameInstance()->GetSubsystem<UDreamingIsland_GIS>();
	Subsystem->LoadLinkData(this);
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

void ALink::SetIsThief(bool bFlag)
{
	StatusComponent->SetIsThief(bFlag);
}

bool ALink::GetIsThief()
{
	return StatusComponent->GetIsThief();
}

void ALink::SetCrane(ACrane* Crane)
{
	StatusComponent->SetCrane(Crane);
}

void ALink::ClearCrane()
{
	StatusComponent->ClearCrane();
}

bool ALink::IsCrane()
{
	if (StatusComponent->GetCrane()) return true;
	return false;
}

void ALink::ActivateSlashEffect()
{
	if (!NiagaraComponent01 || !NiagaraComponent02 || !NiagaraComponent03) return;

	switch (SlashIndex)
	{
	case 0:
		NiagaraComponent01->Activate();
		break;
	case 1:
		NiagaraComponent02->Activate();
		break;
	case 2:
		NiagaraComponent03->Activate();
		break;
	default:
		break;
	}

	SlashIndex = (SlashIndex + 1) % 3;
	//NiagaraComponent01->OnSystemFinished.AddDynamic(this, &ALink::OnSlashEnd);

	UE_LOG(LogTemp, Warning, TEXT("SlashEffect"));

}

//void ALink::OnSlashEnd(UNiagaraComponent* _NiagaraComponent)
//{
//	NiagaraComponent01->Deactivate();
//	NiagaraComponent02->Deactivate();
//	NiagaraComponent03->Deactivate();
//}
