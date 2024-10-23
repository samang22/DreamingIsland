// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/WeaponChildActorComponent.h"
#include "Actors/Weapon/Weapon.h"

UWeaponChildActorComponent::UWeaponChildActorComponent()
{
	SetChildActorClass(AWeapon::StaticClass());
}

void UWeaponChildActorComponent::SetData(FDataTableRowHandle InDataTableRowHandle)
{
	if (InDataTableRowHandle.IsNull()) { return; }
	
	FWeaponTableRow* Data = InDataTableRowHandle.GetRow<FWeaponTableRow>(InDataTableRowHandle.RowName.ToString());
	if (!Data) { ensure(false); return; }

	SetChildActorClass(Data->WeaponClass);

	AActor* tempActor = GetChildActor();
	if (!tempActor)
	{
		return;
	}

	Weapon = Cast<AWeapon>(tempActor);
	check(Weapon);
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	check(OwnerPawn);
	Weapon->SetOwner(OwnerPawn);
	Weapon->SetInstigator(OwnerPawn);
	Weapon->SetData(InDataTableRowHandle);
}

void UWeaponChildActorComponent::RenderOff()
{
	Weapon->RenderOff();
}

void UWeaponChildActorComponent::RenderOn()
{
	Weapon->RenderOn();
}
