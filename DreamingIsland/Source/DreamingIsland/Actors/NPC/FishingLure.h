// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameframework/Actor.h"
#include "FishingLure.generated.h"

class USphereComponent;
class UStaticMeshComponent;
UCLASS()
class DREAMINGISLAND_API AFishingLure : public AActor
{
	GENERATED_BODY()
public:
	AFishingLure();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

protected:
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;
	TObjectPtr<USphereComponent> CollisionComponent;

public:
	void Move(FVector vDir, float ScaleValue);
};
