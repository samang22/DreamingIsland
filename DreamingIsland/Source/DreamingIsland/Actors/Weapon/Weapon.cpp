// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Weapon/Weapon.h"
#include "Components/StatusComponent.h"

FWeaponTableRow::FWeaponTableRow()
	: WeaponClass(AWeapon::StaticClass())
{
}


// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	SkeletalMeshComponent->SetupAttachment(RootComponent);
	SkeletalMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = SkeletalMeshComponent;
}

void AWeapon::SetData(const FDataTableRowHandle& InDataTableRowHandle)
{
	DataTableRowHandle = InDataTableRowHandle;
	if (DataTableRowHandle.IsNull()) { return; }
	FWeaponTableRow* Data = DataTableRowHandle.GetRow<FWeaponTableRow>(TEXT("Weapon"));
	if (!Data) { ensure(false); return; }
	WeaponTableRow = Data;

	SkeletalMeshComponent->SetSkeletalMesh(Data->SkeletalMesh);
	SkeletalMeshComponent->SetRelativeTransform(Data->Transform);
	check(Data->AnimClass);
	USkeletalMeshComponent* MeshComponent = GetOwner()->GetComponentByClass<USkeletalMeshComponent>();
	check(MeshComponent);
	MeshComponent->SetAnimClass(Data->AnimClass);

	// Owner 정보 세팅
	{
		OwningPawn = Cast<APawn>(GetOwner());
		check(OwningPawn);
		OwningPawnBodyMesh = OwningPawn->GetComponentByClass<USkeletalMeshComponent>();
		check(OwningPawnBodyMesh);
		AnimInstance = Cast<UAnimInstance>(MeshComponent->GetAnimInstance());
		check(AnimInstance);
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

