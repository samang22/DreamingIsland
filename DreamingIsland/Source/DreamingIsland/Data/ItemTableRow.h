// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "Misc/Utils.h"

#include "ItemTableRow.generated.h"


USTRUCT()
struct DREAMINGISLAND_API FItemTableRow : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "Item")
	UStaticMesh* SkeletalMesh = nullptr;

	UPROPERTY(EditAnywhere, Category = "Item")
	FTransform MeshTransform = FTransform::Identity;


public:
	UPROPERTY(EditAnywhere, Category = "Item|Collision")
	TSubclassOf<UShapeComponent> CollisionClass;
	UPROPERTY(EditAnywhere, Category = "NPC|Collision")
	float CollisionSphereRadius = 32.f;
	UPROPERTY(EditAnywhere, Category = "Item|Collision")
	FVector CollisionBoxExtent = FVector(32.0, 32.0, 32.0);
	UPROPERTY(EditAnywhere, Category = "Item|Collision")
	float CollisionCapsuleRadius = 22.f;
	UPROPERTY(EditAnywhere, Category = "Item|Collision")
	float CollisionCapsuleHalfHeight = 44.f;

public:
	UPROPERTY(EditAnywhere, Category = "Item|Value")
	int ItemValue = 0;
};
