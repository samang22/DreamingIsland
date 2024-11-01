// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Items/Item.h"
#include "Components/SphereComponent.h"
#include "Misc/Utils.h"
#include "Data/ItemTableRow.h"
#include "Actors/Link/Link.h"
#include "GameFramework/CharacterMovementComponent.h"
//#include "PhysicalMaterials/PhysicalMaterial.h"


#define LINK_LOCATION_OFFSET 70.f
// Sets default values
AItem::AItem(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;



	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	CollisionComponent->SetCollisionProfileName(CollisionProfileName::Item);
	CollisionComponent->SetCanEverAffectNavigation(false);
	CollisionComponent->SetEnableGravity(true);
	CollisionComponent->SetMassOverrideInKg(NAME_None, 10.0f, true);
	CollisionComponent->BodyInstance.bSimulatePhysics = true;
	RootComponent = CollisionComponent;
	//static ConstructorHelpers::FObjectFinder<UPhysicalMaterial> PhysMaterial(TEXT("/Script/PhysicsCore.PhysicalMaterial'/Game/Assets/Item/PM_Item.PM_Item'"));
	//CollisionComponent->SetPhysMaterialOverride(PhysMaterial.Object);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(RootComponent);

}

void AItem::SetData(const FDataTableRowHandle& InDataTableRowHandle)
{
	DataTableRowHandle = InDataTableRowHandle;
	if (DataTableRowHandle.IsNull()) { return; }
	FItemTableRow* Data = DataTableRowHandle.GetRow<FItemTableRow>(DataTableRowHandle.RowName.ToString());
	if (!Data) { return; }
	ItemData = Data;
	
	if (IsValid(CollisionComponent))
	{
		USphereComponent* SphereComponent = Cast<USphereComponent>(CollisionComponent);
		SphereComponent->SetSphereRadius(ItemData->CollisionSphereRadius);
		CollisionComponent->SetCollisionProfileName(CollisionProfileName::Item);
		CollisionComponent->bHiddenInGame = COLLISION_HIDDEN_IN_GAME;
		CollisionComponent->RegisterComponent();
		CollisionComponent->BodyInstance.bSimulatePhysics = true;

	}

	StaticMeshComponent->SetStaticMesh(ItemData->SkeletalMesh);
	StaticMeshComponent->SetRelativeTransform(ItemData->MeshTransform);

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
	SetActorTransform(Transform);
	SetData(DataTableRowHandle);
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
	SetData(DataTableRowHandle);
	CollisionComponent->BodyInstance.bSimulatePhysics = true;
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ItemCatchedSequence(DeltaTime);
}

void AItem::ItemCatchedSequence(float DeltaTime)
{
	if (bIsItemCatched)
	{
		if (CatchingItemActor)
		{
			if (ALink* Link = Cast<ALink>(CatchingItemActor))
			{
				FVector LinkLocation = Link->GetActorLocation();
				LinkLocation.Z += LINK_LOCATION_OFFSET;
				SetActorLocation(LinkLocation);
				SetActorRotation(Link->GetActorRotation());
			}
		}
	}
}