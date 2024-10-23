// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Misc/Utils.h"
#include "Weapon.generated.h"

class AWeapon;
USTRUCT()
struct DREAMINGISLAND_API FWeaponTableRow : public FTableRowBase
{
	GENERATED_BODY()
	FWeaponTableRow();

public: // Base
	UPROPERTY(EditAnywhere, Category = "Weapon")
	UStaticMesh* StaticMesh = nullptr;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	FTransform Transform = FTransform::Identity;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	TSubclassOf<AWeapon> WeaponClass;
};

UCLASS()
class DREAMINGISLAND_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	AWeapon();
	virtual void SetData(const FDataTableRowHandle& InDataTableRowHandle);

protected:
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMeshComponent;

protected: // Owner
	// 이 무기의 소유권자 Pawn
	APawn* OwningPawn = nullptr;
	// 이 무기의 소유권자 Pawn의 SkeletalMeshComponent로 캐릭터의 MeshComponent 같은 것을 의미
	USkeletalMeshComponent* OwningPawnBodyMesh = nullptr;

	UAnimInstance* AnimInstance = nullptr;

	UPROPERTY()
	class UStatusComponent* OwnerStatusComponent = nullptr;

protected:
	UPROPERTY(EditAnywhere, meta = (RowType = "WeaponTableRow"))
	FDataTableRowHandle DataTableRowHandle;

	const FWeaponTableRow* WeaponTableRow = nullptr;
};
