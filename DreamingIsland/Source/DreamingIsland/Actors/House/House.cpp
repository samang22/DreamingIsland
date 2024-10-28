// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/House/House.h"
#include "Data/HouseTableRow.h"
#include "Misc/Utils.h"
#include "Data/HouseTableRow.h"


// Sets default values
AHouse::AHouse()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AHouse::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

// Called when the game starts or when spawned
void AHouse::BeginPlay()
{
	Super::BeginPlay();
}

void AHouse::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	SetData(DataTableRowHandle);
	SetActorTransform(Transform);
}

// Called every frame
void AHouse::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHouse::SetData(const FDataTableRowHandle& InDataTableRowHandle)
{
	DataTableRowHandle = InDataTableRowHandle;
	if (DataTableRowHandle.IsNull()) { return; }
	FHouseTableRow* Data = DataTableRowHandle.GetRow<FHouseTableRow>(DataTableRowHandle.RowName.ToString());
	if (!Data) { return; }
	HouseData = Data;

	StaticMeshComponent->SetStaticMesh(HouseData->StaticMesh);
	StaticMeshComponent->SetRelativeTransform(HouseData->MeshTransform);
}

void AHouse::PostDuplicate(EDuplicateMode::Type DuplicateMode)
{
	Super::PostDuplicate(DuplicateMode);

	if (DuplicateMode == EDuplicateMode::Normal)
	{
		FTransform Backup = GetActorTransform();
		SetData(DataTableRowHandle);
		SetActorTransform(Backup);
	}
}

void AHouse::PostLoad()
{
	Super::PostLoad();
}

void AHouse::PostLoadSubobjects(FObjectInstancingGraph* OuterInstanceGraph)
{
	Super::PostLoadSubobjects(OuterInstanceGraph);
}

