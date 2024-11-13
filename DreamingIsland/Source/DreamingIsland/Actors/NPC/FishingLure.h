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
	UPROPERTY()
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;
	UPROPERTY()
	TObjectPtr<USphereComponent> CollisionComponent;

public:
	void Move(FVector vDir, float ScaleValue);

protected:
	TObjectPtr<AActor> FollowingActor;
public:
	void SetFollowingActor(AActor* FA);
	AActor* GetFollowingActor() const { return FollowingActor; }

protected:
	TObjectPtr<UPhysicalMaterial> PhysicalMaterial = nullptr;

public:
	void AddForce(FVector Velocity);

protected:
	FVector PrevLocation = FVector::ZeroVector;

};
