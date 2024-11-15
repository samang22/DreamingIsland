// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameframework/Pawn.h"
#include "FishingLure.generated.h"

class USphereComponent;
class UStaticMeshComponent;
class AFish;
UCLASS()
// to be sensed by AIPerception, FishingLure overrides Pawn, not Actor
class DREAMINGISLAND_API AFishingLure : public APawn
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
	UPROPERTY()
	TObjectPtr<USphereComponent> GetFishCollisionComponent;

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


protected:
	TObjectPtr<AFish> CurrentFish = nullptr;

protected:
	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	virtual void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	void PullFish();
};
