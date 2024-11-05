// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/House/House.h"
#include "CraneGame.generated.h"

class UMaterialInstanceDynamic;
UCLASS()
class DREAMINGISLAND_API ACraneGame : public AHouse
{
	GENERATED_BODY()
public:
	ACraneGame(const FObjectInitializer& ObjectInitializer);
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;


protected:
	UPROPERTY(EditAnywhere)
	FVector4 UV = FVector4(0.0, 0.0, 1.0, 1.0);
	UPROPERTY()
	UMaterialInstanceDynamic* MID = nullptr;
};
