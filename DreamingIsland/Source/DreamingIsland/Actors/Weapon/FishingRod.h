// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FishingRod.generated.h"

class UFishingRodStatusComponent;
UCLASS()
class DREAMINGISLAND_API AFishingRod : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFishingRod();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UFishingRodStatusComponent> StatusComponent;

public:
	TObjectPtr<UFishingRodStatusComponent> GetStatusComponent() { return StatusComponent; }

public:
	FVector GetFishingRodEndLocation() const;
};
