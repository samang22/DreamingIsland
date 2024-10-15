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

public:
	UPROPERTY(EditAnywhere, Category = "Projectile")
	UStaticMesh* StaticMesh = nullptr;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	FTransform Transform = FTransform::Identity;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	TSubclassOf<class AProjectile> ProjectileClass;

	// @TODO : Hit Effect
};
