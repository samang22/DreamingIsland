// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Water.generated.h"

class UMaterialInstanceDynamic;
struct FWaterTableRow;
UCLASS()
class DREAMINGISLAND_API AWater : public AActor
{
	GENERATED_BODY()
	
public:
	AWater();

public:
	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

protected:
	FVector4 UV_Parameter01 = FVector4(0.0, 0.0, 1.0, 1.0);
	double SinAlpha = 0.0;
	FVector4 UV_Parameter02 = FVector4(0.0, 0.0, 1.0, 1.0);
	UPROPERTY()
	UMaterialInstanceDynamic* MID = nullptr;
};
