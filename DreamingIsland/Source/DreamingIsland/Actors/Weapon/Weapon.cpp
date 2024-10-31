// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Weapon/Weapon.h"
#include "Components/StatusComponent/StatusComponent.h"

FWeaponTableRow::FWeaponTableRow()
	: WeaponClass(AWeapon::StaticClass())
{
}


// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = StaticMeshComponent;
}

void AWeapon::SetData(const FDataTableRowHandle& InDataTableRowHandle)
{
	DataTableRowHandle = InDataTableRowHandle;
	if (DataTableRowHandle.IsNull()) { return; }
	FWeaponTableRow* Data = DataTableRowHandle.GetRow<FWeaponTableRow>(TEXT("Weapon"));
	if (!Data) { ensure(false); return; }
	WeaponTableRow = Data;

	StaticMeshComponent->SetStaticMesh(Data->StaticMesh);
	StaticMeshComponent->SetRelativeTransform(Data->Transform);

	// Owner 정보 세팅
	{
		OwningPawn = Cast<APawn>(GetOwner());
		check(OwningPawn);
		OwningPawnBodyMesh = OwningPawn->GetComponentByClass<USkeletalMeshComponent>();
		check(OwningPawnBodyMesh);
	}
}

void AWeapon::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeapon::RenderOff()
{
	StaticMeshComponent->SetVisibility(false);
	StaticMeshComponent->SetHiddenInGame(true);
}

void AWeapon::RenderOn()
{
	StaticMeshComponent->SetVisibility(true);
	StaticMeshComponent->SetHiddenInGame(false);
}

