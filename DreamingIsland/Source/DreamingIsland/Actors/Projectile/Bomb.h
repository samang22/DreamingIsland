// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameframework/Actor.h"
#include "Bomb.generated.h"

class USphereComponent;
UCLASS()
class DREAMINGISLAND_API ABomb : public AActor
{
	GENERATED_BODY()
public:
	ABomb();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

protected:
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;
	TObjectPtr<USphereComponent> CollisionComponent;

//protected:
//	TObjectPtr<UPhysicalMaterial> PhysicalMaterial = nullptr;

protected:
	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

public:
	void Explosion();
	void SpawnProjectile();
};
