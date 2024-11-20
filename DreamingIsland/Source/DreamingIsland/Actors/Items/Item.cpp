// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Items/Item.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "Misc/Utils.h"
#include "Data/ItemTableRow.h"
#include "Actors/Link/Link.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Actors/NPC/Crane.h"


// Sets default values
AItem::AItem(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;
	static ConstructorHelpers::FObjectFinder<UPhysicalMaterial> PhysMaterial(TEXT("/Script/PhysicsCore.PhysicalMaterial'/Game/Assets/Item/PM_Item.PM_Item'"));
	PhysicalMaterial = PhysMaterial.Object;
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
}

void AItem::SetData(const FDataTableRowHandle& InDataTableRowHandle)
{
	DataTableRowHandle = InDataTableRowHandle;
	if (DataTableRowHandle.IsNull()) { return; }
	FItemTableRow* Data = DataTableRowHandle.GetRow<FItemTableRow>(DataTableRowHandle.RowName.ToString());
	if (!Data) { return; }
	ItemData = Data;

	if (!IsValid(CollisionComponent) && ItemData->CollisionClass)
	{
		EObjectFlags SubobjectFlags = GetMaskedFlags(RF_PropagateToSubObjects) | RF_DefaultSubObject;
		CollisionComponent = NewObject<UShapeComponent>(this, ItemData->CollisionClass, TEXT("CollisionComponent"), SubobjectFlags);
		CollisionComponent->RegisterComponent();
		CollisionComponent->SetCollisionProfileName(CollisionProfileName::Item);
		CollisionComponent->SetCanEverAffectNavigation(false);
		SetRootComponent(CollisionComponent);
		DefaultSceneRoot->SetRelativeTransform(FTransform::Identity);
		DefaultSceneRoot->AttachToComponent(CollisionComponent, FAttachmentTransformRules::KeepRelativeTransform);

		if (!HasAnyFlags(RF_ClassDefaultObject))
		{
			CollisionComponent->SetPhysMaterialOverride(PhysicalMaterial);
			CollisionComponent->SetEnableGravity(true);
			CollisionComponent->SetSimulatePhysics(true);
		}
		if (USphereComponent* SphereComponent = Cast<USphereComponent>(CollisionComponent))
		{
			SphereComponent->SetSphereRadius(ItemData->CollisionSphereRadius);
		}
		else if (UBoxComponent* BoxComponent = Cast<UBoxComponent>(CollisionComponent))
		{
			BoxComponent->SetBoxExtent(ItemData->CollisionBoxExtent);
		}
		else if (UCapsuleComponent* CapsuleComponent = Cast<UCapsuleComponent>(CollisionComponent))
		{
			CapsuleComponent->SetCapsuleSize(ItemData->CollisionCapsuleRadius, ItemData->CollisionCapsuleHalfHeight);
		}
	}

	StaticMeshComponent->SetStaticMesh(ItemData->SkeletalMesh);
	StaticMeshComponent->SetRelativeTransform(ItemData->MeshTransform);
	StaticMeshComponent->AttachToComponent(CollisionComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ItemValue = ItemData->ItemValue;
}

void AItem::PostDuplicate(EDuplicateMode::Type DuplicateMode)
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

void AItem::PostLoad()
{
	Super::PostLoad();
}

void AItem::PostLoadSubobjects(FObjectInstancingGraph* OuterInstanceGraph)
{
	Super::PostLoadSubobjects(OuterInstanceGraph);
}

void AItem::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	// nothing to do
}

void AItem::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	SetData(DataTableRowHandle);
	SetActorTransform(Transform);
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
	SetData(DataTableRowHandle);
	CollisionComponent->SetSimulatePhysics(true);
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//ItemCatchedSequence(DeltaTime);
	//if (Magnet && Magnet->GetIsMagnetic())
	//{


	//	CollisionComponent->AddForce(MAGNET_FORCE * Direction);
	//}
}

void AItem::AddForce(FVector _Direction, float Force)
{
	CollisionComponent->AddForce(Force * _Direction);
}

//void AItem::ItemCatchedSequence(float DeltaTime)
//{
//	if (bIsItemCatched)
//	{
//		if (CatchingItemActor)
//		{
//			if (ALink* Link = Cast<ALink>(CatchingItemActor))
//			{
//				FVector LinkLocation = Link->GetActorLocation();
//				//UE_LOG(LogTemp, Warning, TEXT("Item Height : %f"), LinkLocation.Z);
//
//				LinkLocation.Z += LINK_LOCATION_OFFSET;
//
//				SetActorLocation(LinkLocation);
//				SetActorRotation(Link->GetActorRotation());
//			}
//		}
//	}
//}
//
void AItem::SetItemPhysics(bool bFlag)
{
	CollisionComponent->SetSimulatePhysics(bFlag);
}
