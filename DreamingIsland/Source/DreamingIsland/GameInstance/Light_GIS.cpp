// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstance/Light_GIS.h"
#include "Actors/Lights/MyDirectionalLight.h"
#include "Components/DirectionalLightComponent.h"
#include "Engine/ExponentialHeightFog.h"
#include "Kismet/GameplayStatics.h"

void ULight_GIS::Initialize(FSubsystemCollectionBase& Collection)
{
	// 특정 클래스를 상속한 첫 번째 액터를 찾기
	HeightFog = Cast<AExponentialHeightFog>(UGameplayStatics::GetActorOfClass(GetWorld(), AExponentialHeightFog::StaticClass()));
	if (HeightFog)
	{
		HeightFog->SetActorHiddenInGame(true);
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

	if (HeightFog)
	{
		HeightFog->SetActorHiddenInGame(false);
	}
	else
	{
		HeightFog = Cast<AExponentialHeightFog>(UGameplayStatics::GetActorOfClass(GetWorld(), AExponentialHeightFog::StaticClass()));
		if (HeightFog)
		{
			HeightFog->SetActorHiddenInGame(false);
		}

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
		HeightFog->SetActorHiddenInGame(true);
	}
	else
	{
		HeightFog = Cast<AExponentialHeightFog>(UGameplayStatics::GetActorOfClass(GetWorld(), AExponentialHeightFog::StaticClass()));
		if (HeightFog)
		{
			HeightFog->SetActorHiddenInGame(true);
		}

	}
}
