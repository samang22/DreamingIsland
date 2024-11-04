// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingFloorCrane.generated.h"

class USplineComponent;
UCLASS()
class DREAMINGISLAND_API AMovingFloorCrane : public AActor
{
	GENERATED_BODY()
	
public:
	AMovingFloorCrane();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;
	UPROPERTY(EditAnywhere)
	TObjectPtr<USplineComponent> SplineComponent;

protected:
	bool bMove = false;
	bool bMoveRight = true;
	float fDistanceAlongSpline = 0.f;

public:
	void SetMove(bool bFlag) { bMove = bFlag; }
};
