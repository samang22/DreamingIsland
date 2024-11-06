// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CraneFence.generated.h"

class USplineComponent;
UCLASS()
class DREAMINGISLAND_API ACraneFence : public AActor
{
	GENERATED_BODY()
public:
	ACraneFence();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;
	UPROPERTY(EditAnywhere)
	TObjectPtr<USplineComponent> SplineComponent;

protected:
	bool bMoveUp = true;
	float fDistanceAlongSpline = 0.f;

public:
	void SetMoveUp(bool bFlag) { bMoveUp = bFlag; }
};
