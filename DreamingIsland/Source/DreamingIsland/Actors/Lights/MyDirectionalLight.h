// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyDirectionalLight.generated.h"

class UDirectionalLightComponent;
UCLASS()
class DREAMINGISLAND_API AMyDirectionalLight : public AActor
{
	GENERATED_BODY()
	
public:	
	AMyDirectionalLight();

protected: 
	UPROPERTY(VisibleAnywhere, Category = "Light")
	TObjectPtr<UDirectionalLightComponent> DirectionalLightComponent;
public:
	//UDirectionalLightComponent* GetLightComponent() { return DirectionalLightComponent; }


public:
	void ToDarkForest();
	void ToForest();

protected:
	bool bToDarkForest = false;

protected:
	virtual void BeginPlay() override;
public:	
	virtual void Tick(float DeltaTime) override;
};
