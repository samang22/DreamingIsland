// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Misc/Utils.h"

#include "WaterTableRow.generated.h"

USTRUCT()
struct DREAMINGISLAND_API FWaterTableRow : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "StaticMesh")
	TObjectPtr<UStaticMesh> StaticMesh = nullptr;

public:
	UPROPERTY(EditAnywhere, Category = "MaterialInstanceDynamic")
	TObjectPtr<UMaterialInstanceDynamic> MID = nullptr;
};
