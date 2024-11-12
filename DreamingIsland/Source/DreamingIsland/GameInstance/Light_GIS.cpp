// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstance/Light_GIS.h"
#include "Actors/Lights/MyDirectionalLight.h"
#include "Components/DirectionalLightComponent.h"
#include "Engine/ExponentialHeightFog.h"
#include "Kismet/GameplayStatics.h"
#include "Components/ExponentialHeightFogComponent.h"
#include "Actors/ShaderEffect/ExponentialHeightFogHolder.h"

#define FOG_DENSITY 5.f

void ULight_GIS::Initialize(FSubsystemCollectionBase& Collection)
{
	AExponentialHeightFog* HeightFog = Cast<AExponentialHeightFog>(UGameplayStatics::GetActorOfClass(GetWorld(), AExponentialHeightFog::StaticClass()));
	if (HeightFog && HeightFogHolder)
	{
		HeightFogHolder->SetHeightFog(HeightFog);
	}
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

	if (HeightFogHolder)
	{
		HeightFogHolder->SetGoalFogDensity(FOG_DENSITY);
	}
}

void ULight_GIS::SetForest()
{
	if (DirectionalLight)
	{
		DirectionalLight->ToForest();
	}

	if (HeightFogHolder)
	{
		HeightFogHolder->SetGoalFogDensity(0.f);
	}
}
