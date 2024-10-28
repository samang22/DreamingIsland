// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Misc/Utils.h"
#include "InvisibleColliderTableRow.generated.h"

/**
 * 
 */
USTRUCT()
struct DREAMINGISLAND_API FInvisibleColliderTableRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Collision")
	TSubclassOf<UShapeComponent> CollisionClass;
	UPROPERTY(EditAnywhere, Category = "Collision")
	float CollisionSphereRadius = 32.f;
	UPROPERTY(EditAnywhere, Category = "Collision")
	FVector CollisionBoxExtent = FVector(32.0, 32.0, 32.0);
	UPROPERTY(EditAnywhere, Category = "Collision")
	float CollisionCapsuleRadius = 22.f;
	UPROPERTY(EditAnywhere, Category = "Collision")
	float CollisionCapsuleHalfHeight = 44.f;


};
