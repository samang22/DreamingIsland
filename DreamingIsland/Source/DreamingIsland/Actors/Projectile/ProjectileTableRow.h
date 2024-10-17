// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectileTableRow.generated.h"

/**
 * 
 */
USTRUCT()
struct DREAMINGISLAND_API FProjectileTableRow : public FTableRowBase
{
	GENERATED_BODY()
	FProjectileTableRow();

//public:
//	UPROPERTY(EditAnywhere, meta = (RowType = "ProjectileTableRow"))
//	FDataTableRowHandle ProjectileRowHandle;

public:
	UPROPERTY(EditAnywhere, Category = "Projectile")
	UStaticMesh* StaticMesh = nullptr;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	FTransform Transform = FTransform::Identity;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	TSubclassOf<class AProjectile> ProjectileClass;


public:
	UPROPERTY(EditAnywhere, Category = "Collision")
	TSubclassOf<UShapeComponent> CollisionClass/* = USphereComponent::StaticClass()*/;
	UPROPERTY(EditAnywhere, Category = "Collision")
	float CollisionSphereRadius = 32.f;
	UPROPERTY(EditAnywhere, Category = "Collision")
	FVector CollisionBoxExtent = FVector(32.0, 32.0, 32.0);
	UPROPERTY(EditAnywhere, Category = "Collision")
	float CollisionCapsuleRadius = 22.f;
	UPROPERTY(EditAnywhere, Category = "Collision")
	float CollisionCapsuleHalfHeight = 44.f;



	// @TODO : Hit Effect
public:
	UPROPERTY(EditAnywhere, Category = "Damage")
	float Damage = 0.f;
};
