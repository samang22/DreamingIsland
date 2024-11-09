// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"

#include "Light_GIS.generated.h"

class AMyDirectionalLight;
UCLASS()
class DREAMINGISLAND_API ULight_GIS : public UGameInstanceSubsystem
{
	GENERATED_BODY()

protected:
	TObjectPtr<AMyDirectionalLight> DirectionalLight;

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

public:
	void RegistDirectionalLight(AMyDirectionalLight* _DirectionalLight) { DirectionalLight = _DirectionalLight; };

public:
	void SetDarkForest(); 
	void SetForest();
};
