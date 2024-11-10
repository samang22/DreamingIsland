// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstance/Light_GIS.h"
#include "Actors/Lights/MyDirectionalLight.h"
#include "Actors/ShaderEffect/MyExponentialHeightFog.h"
#include "Components/DirectionalLightComponent.h"

void ULight_GIS::Initialize(FSubsystemCollectionBase& Collection)
{
}

void ULight_GIS::Deinitialize()
{
}

void ULight_GIS::SetDarkForest()
{
	if (DirectionalLight)
	{
		DirectionalLight->ToDarkForest();
	}

	if (HeightFog)
	{
		HeightFog->SetHeightFogActive();
	}
}

void ULight_GIS::SetForest()
{
	if (DirectionalLight)
	{
		DirectionalLight->ToForest();
	}

	if (HeightFog)
	{
		HeightFog->SetHeightFogActive();
	}
}
