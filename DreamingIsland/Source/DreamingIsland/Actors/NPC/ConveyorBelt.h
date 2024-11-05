// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ConveyorBelt.generated.h"

class UBoxComponent;
class USplineComponent;
UCLASS()
class DREAMINGISLAND_API AConveyorBelt : public AActor
{
	GENERATED_BODY()
	
public:	
	AConveyorBelt();
protected:
	virtual void BeginPlay() override;
public:	
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> DefaultSceneRoot;
	UPROPERTY(VisibleAnywhere)
	TArray<TObjectPtr<UBoxComponent>> CollisionComponent_Array;
	UPROPERTY(EditAnywhere)
	TObjectPtr<USplineComponent> SplineComponent;
	TArray<float> fDistanceAlongSpline_Array;
protected:
	UPhysicalMaterial* PhysicalMaterial = nullptr;

protected:
	bool bMove = false;
};
