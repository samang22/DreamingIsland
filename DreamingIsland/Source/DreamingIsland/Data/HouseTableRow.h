// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HouseTableRow.generated.h"
/**
 * 
 */
USTRUCT()
struct DREAMINGISLAND_API FHouseTableRow
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "Mesh")
	UStaticMesh* StaticMesh = nullptr;

	UPROPERTY(EditAnywhere, Category = "Light")
	FTransform MeshTransform = FTransform::Identity;

	UPROPERTY(EditAnywhere, Category = "Light")
	FTransform DirectionalLightTransform = FTransform::Identity;
};
