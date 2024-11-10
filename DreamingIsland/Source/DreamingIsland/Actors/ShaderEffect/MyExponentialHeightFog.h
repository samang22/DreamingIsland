// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyExponentialHeightFog.generated.h"

class UExponentialHeightFogComponent;
UCLASS()
class DREAMINGISLAND_API AMyExponentialHeightFog : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyExponentialHeightFog();

protected:
	virtual void BeginPlay() override;
public:	
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere)
	UExponentialHeightFogComponent* HeightFogComponent = nullptr;

public:
	void SetHeightFogActive();
	void SetHeightFogDeActive();
};
