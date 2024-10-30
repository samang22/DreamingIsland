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
	float CollisionSphereRadius = 32.f;
};
