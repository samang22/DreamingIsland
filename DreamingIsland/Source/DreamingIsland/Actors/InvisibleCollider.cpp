// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/InvisibleCollider.h"
#include "Data/InvisibleColliderTableRow.h"


// Sets default values
AInvisibleCollider::AInvisibleCollider(const FObjectInitializer& ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;

}

void AInvisibleCollider::SetData(const FDataTableRowHandle& InDataTableRowHandle)
{
	DataTableRowHandle = InDataTableRowHandle;
	if (DataTableRowHandle.IsNull()) { return; }
	FInvisibleColliderTableRow* Data = DataTableRowHandle.GetRow<FInvisibleColliderTableRow>(DataTableRowHandle.RowName.ToString());
	if (!Data) { return; }
	InvisibleColliderData = Data;

	if (!IsValid(CollisionComponent) || CollisionComponent->GetClass() != InvisibleColliderData->CollisionClass)
	{
		EObjectFlags SubobjectFlags = GetMaskedFlags(RF_PropagateToSubObjects) | RF_DefaultSubObject;
		CollisionComponent = NewObject<UShapeComponent>(this, InvisibleColliderData->CollisionClass, TEXT("CollisionComponent"), SubobjectFlags);
		CollisionComponent->RegisterComponent();
		CollisionComponent->SetCollisionProfileName(CollisionProfileName::MapMesh);
		CollisionComponent->SetCanEverAffectNavigation(false);
		SetRootComponent(CollisionComponent);
		DefaultSceneRoot->SetRelativeTransform(FTransform::Identity);
		DefaultSceneRoot->AttachToComponent(CollisionComponent, FAttachmentTransformRules::KeepRelativeTransform);
	}

	if (USphereComponent* SphereComponent = Cast<USphereComponent>(CollisionComponent))
	{
		SphereComponent->SetSphereRadius(InvisibleColliderData->CollisionSphereRadius);
	}
	else if (UBoxComponent* BoxComponent = Cast<UBoxComponent>(CollisionComponent))
	{
		BoxComponent->SetBoxExtent(InvisibleColliderData->CollisionBoxExtent);
	}
	else if (UCapsuleComponent* CapsuleComponent = Cast<UCapsuleComponent>(CollisionComponent))
	{
		CapsuleComponent->SetCapsuleSize(InvisibleColliderData->CollisionCapsuleRadius, InvisibleColliderData->CollisionCapsuleHalfHeight);
	}
}

void AInvisibleCollider::PostDuplicate(EDuplicateMode::Type DuplicateMode)
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

void AInvisibleCollider::PostLoad()
{
	Super::PostLoad();
}

void AInvisibleCollider::PostLoadSubobjects(FObjectInstancingGraph* OuterInstanceGraph)
{
	Super::PostLoadSubobjects(OuterInstanceGraph);
}

void AInvisibleCollider::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

// Called when the game starts or when spawned
void AInvisibleCollider::BeginPlay()
{
	Super::BeginPlay();
	SetData(DataTableRowHandle);
}

void AInvisibleCollider::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	SetData(DataTableRowHandle);
	SetActorTransform(Transform);
}


