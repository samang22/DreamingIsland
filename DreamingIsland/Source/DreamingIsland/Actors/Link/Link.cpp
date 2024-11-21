// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Link/Link.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Components/SoftWheelSpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SoftWheelSpringArmComponent.h"
#include "Components/StatusComponent/LinkStatusComponent.h"
#include "Components/SphereComponent.h"
#include "Components/SpotLightComponent.h"
#include "Components/RectLightComponent.h"

#include "Actors/Projectile/ProjectileTableRow.h"
#include "Actors/Monsters/Hinox.h"
#include "Actors/NPC/NPC.h"
#include "Actors/Items/Item.h"
#include "Actors/Link/LinkController.h"
#include "Actors/NPC/Cucco.h"
#include "Actors/Projectile/Bomb.h"

#include "Animation/LinkAnimInstance.h"
#include "GameInstance/DreamingIsland_GIS.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"


#define SLASH_EFFECT_OFFSET								10.f
#define SLASH_EFFECT_NUM								3



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

	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> NiagaraAsset(TEXT("/Script/Niagara.NiagaraSystem'/Game/Assets/FxER_StylizedSlash/Niagara/Fantasy/NS_sm01_Fantasy_Slash_03_G.NS_sm01_Fantasy_Slash_03_G'"));
	for (int i = 0; i < SLASH_EFFECT_NUM; ++i)
	{
		FString ComponentName = FString::Printf(TEXT("NiagaraComponent_%d"), i);
		SlashEffectComponent_Array.Push(CreateDefaultSubobject<UNiagaraComponent>(*ComponentName));
		//SlashEffectComponent_Array[i]->SetupAttachment(RootComponent);
		SlashEffectComponent_Array[i]->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
		if (NiagaraAsset.Object)
		{
			SlashEffectComponent_Array[i]->SetAsset(NiagaraAsset.Object);
		}
		FRotator CurrentRotation = SlashEffectComponent_Array[i]->GetRelativeRotation();
		FRotator NewRotation = FRotator(CurrentRotation.Pitch + 90.0f, CurrentRotation.Yaw + 180.f, CurrentRotation.Roll);
		//FRotator NewRotation = FRotator(CurrentRotation.Pitch, CurrentRotation.Yaw, CurrentRotation.Roll);
		SlashEffectComponent_Array[i]->SetRelativeRotation(NewRotation);
		SlashEffectComponent_Array[i]->SetRelativeLocation(GetActorForwardVector() * SLASH_EFFECT_OFFSET);
		SlashEffectComponent_Array[i]->SetAutoActivate(false);
	}


	SpotLightComponent = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotLightComponent"));
	SpotLightComponent->SetupAttachment(RootComponent);
	SpotLightComponent->SetInnerConeAngle(0.f);
	SpotLightComponent->SetOuterConeAngle(LINK_SPOTLIGHT_ANGLE);
	SpotLightComponent->SetRelativeLocation(FVector(0.0, 0.0, 200.0));
	FRotator CurrentSpotLightRotator = SpotLightComponent->GetRelativeRotation();
	CurrentSpotLightRotator.Pitch += 270.0;
	SpotLightComponent->SetRelativeRotation(CurrentSpotLightRotator);
	SpotLightComponent->Intensity = LINK_SPOTLIGHT_INTENSITY;
	SpotLightComponent->SetActive(false);


	//RectLightComponent = CreateDefaultSubobject<URectLightComponent>(TEXT("RectLightComponent"));
	//RectLightComponent->SetupAttachment(RootComponent);
	//RectLightComponent->SetRelativeLocation(FVector(0.0, 0.0, 300.0));
	//RectLightComponent->Intensity = LINK_SPOTLIGHT_INTENSITY;
	//RectLightComponent->SetActive(false);

	MID_Array.Reserve(static_cast<uint32>(LINK_MATERIAL::END));


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

	SetSpotLightActive(false);

	USkeletalMeshComponent* SkeletalMeshComponent = GetMesh();
	// CreateDynamicMaterialInstance func must called in BeginPlay not Constructor
	for (uint8 i = 0; i < static_cast<uint8>(LINK_MATERIAL::END); ++i)
	{
		MID_Array.Push(SkeletalMeshComponent->CreateDynamicMaterialInstance(i));
	}

	for (uint8 i = 0; i < static_cast<uint8>(LINK_MATERIAL::END); ++i)
	{
		bool bFlag = false;
		switch (static_cast<LINK_MATERIAL>(i))
		{
		case LINK_MATERIAL::SHIELDA:
			bFlag = StatusComponent->GetToolEquipStatus(LINK_TOOL_BIT_SHIELD);
			break;
		case LINK_MATERIAL::SWORDA:
		case LINK_MATERIAL::SWORDA_BALL:
			bFlag = StatusComponent->GetToolEquipStatus(LINK_TOOL_BIT_SWORD);
			break;
		case LINK_MATERIAL::FLIPPERS:
		case LINK_MATERIAL::HOOKSHOT:
		case LINK_MATERIAL::MAGICROD:
		case LINK_MATERIAL::OCARINA:
		case LINK_MATERIAL::SHIELDB:
		case LINK_MATERIAL::SHIELDB_MIRROR:
		case LINK_MATERIAL::SWORDB:
		case LINK_MATERIAL::SWORDB_BALL:
		case LINK_MATERIAL::SHOVEL:
			bFlag = false;
			break;
		default:
			break;
		}
		FName Name_Opacity = FName(TEXT("Opacity"));
		MID_Array[i]->SetScalarParameterValue(Name_Opacity, bFlag ? 1.f : 0.f);

	}

	LinkController->OnLinkItemGet.AddDynamic(this, &ThisClass::OnLinkItemGet);
	LinkController->OnLinkItemGetEnd.AddDynamic(this, &ThisClass::OnLinkItemGetEnd);
};

void ALink::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

// Called every frame
void ALink::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bCameraZoom)
	{
		FVector tempLocation = FMath::Lerp(Camera->GetComponentLocation(), DesiredCameraLocation, 0.1f);
		FRotator tempRotator = FMath::Lerp(Camera->GetComponentRotation(), DesiredCameraRotator, 0.1f);
		Camera->SetWorldLocationAndRotation(tempLocation, tempRotator);
	}

	if (CatchingActor)
	{
		CatchingActor->SetActorLocation(GetActorLocation() + FVector(0.0, 0.0, LINK_ITEM_OFFSET));
		CatchingActor->SetActorRotation(GetActorRotation());
	}


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

void ALink::OnLinkItemGet(FVector LinkLocation, FVector ForwardVector)
{
	DefaultCameraLocation = Camera->GetComponentLocation();
	DefaultCameraRotator = Camera->GetComponentRotation();

	bCameraZoom = true;

	FVector tempLocation = GetActorLocation();
	tempLocation += FVector(0.0, 1.0, 0.0) * LINK_ITEM_GET_FORWARD_OFFSET;
	tempLocation += FVector(0., 0., 1.) * LINK_ITEM_GET_UP_OFFSET;

	DesiredCameraLocation = tempLocation;

	FVector NewVector = GetActorLocation() - DesiredCameraLocation;
	NewVector.Normalize();

	float Pitch = FMath::Asin(NewVector.Z) * (180.0f / PI);
	float Yaw = FMath::Atan2(NewVector.Y, NewVector.X) * (180.0f / PI);
	DesiredCameraRotator = FRotator(Pitch, Yaw, 0.f);

	FVector NewLinkLook = FVector(0.0, 1.0, 0.0);
	Pitch = FMath::Asin(NewLinkLook.Z) * (180.0f / PI);
	Yaw = FMath::Atan2(NewLinkLook.Y, NewLinkLook.X) * (180.0f / PI);
	SetActorRotation(FRotator(Pitch, Yaw, 0.f));
}

void ALink::OnLinkItemGetEnd()
{
	bCameraZoom = false;
	Camera->SetWorldLocationAndRotation(DefaultCameraLocation, DefaultCameraRotator);
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
	GetStatusComponent()->SetOnAnimationStatus(LINK_BIT_BATABATA);
}

void ALink::ResumeMovement()
{
	UCharacterMovementComponent* Movement = GetCharacterMovement();
	Movement->MaxWalkSpeed = LINK_WALK_SPEED;
	GetStatusComponent()->SetOffAnimationStatus(LINK_BIT_BATABATA);
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
	if (!OverlappedItem || CatchingActor) return;
	if (AItem* Item = Cast<AItem>(OverlappedItem))
	{
		CatchingActor = OverlappedItem;
		OverlappedItem = nullptr;
		StatusComponent->SetOnAnimationStatus(LINK_BIT_CARRY);
		Item->SetItemPhysics(false);
	}
}

void ALink::ActorThrown()
{
	if (!CatchingActor) return;
	if (AItem* Item = Cast<AItem>(CatchingActor))
	{
		Item->SetItemPhysics(true);
	}
	CatchingActor = nullptr;
	StatusComponent->SetOffAnimationStatus(LINK_BIT_CARRY);
}

bool ALink::IsCatchingActor()
{
	return CatchingActor ? true : false;
}

void ALink::SetCatchingActor(AActor* _Actor)
{
	if (ABomb* Bomb = Cast<ABomb>(_Actor))
	{
		StatusComponent->SetOnAnimationStatus(LINK_BIT_CARRY);
		CatchingActor = _Actor;
	}
}

void ALink::DestoryCatchingItem()
{
	if (!CatchingActor) return;
	StatusComponent->SetOffAnimationStatus(LINK_BIT_CARRY);
	CatchingActor->Destroy();
	CatchingActor = nullptr;
}

void ALink::SetOffAnimStatus(uint8 Bit)
{
	StatusComponent->SetOffAnimationStatus(Bit);
}

void ALink::CatchCucco()
{
	if (!OverlappedNPC) return;
	
	if (ACucco* Cucco = Cast<ACucco>(OverlappedNPC))
	{
		CatchingActor = OverlappedNPC;
		OverlappedNPC = nullptr;
		StatusComponent->SetOnAnimationStatus(LINK_BIT_CARRY);
	}
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
	SlashEffectComponent_Array[SlashEffectIndex]->Activate();
	SlashEffectIndex = (SlashEffectIndex + 1) % SLASH_EFFECT_NUM;
}

void ALink::SetSpotLightActive(bool bFlag)
{
	SpotLightComponent->SetVisibility(bFlag);

}

void ALink::SetRectLightActive(bool bFlag)
{
	RectLightComponent->SetVisibility(bFlag);
}

void ALink::SetMaterialOpacity(LINK_MATERIAL eMaterial, float Opacity)
{
	FName Name_Opacity = FName(TEXT("Opacity"));
	MID_Array[static_cast<int>(eMaterial)]->SetScalarParameterValue(Name_Opacity, Opacity);
}
