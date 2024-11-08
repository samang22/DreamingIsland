// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HouseTableRow.generated.h"


USTRUCT()
struct DREAMINGISLAND_API FHouseTableRow : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "Mesh")
	TObjectPtr<UStaticMesh> StaticMesh = nullptr;

	UPROPERTY(EditAnywhere, Category = "Mesh")
	FTransform MeshTransform = FTransform::Identity;

public:
	UPROPERTY(EditAnywhere, Category = "Light")
	FTransform DirectionalLightTransform = FTransform::Identity;
};
