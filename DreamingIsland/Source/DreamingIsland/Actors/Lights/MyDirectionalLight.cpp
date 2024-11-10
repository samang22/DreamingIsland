// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Lights/MyDirectionalLight.h"
#include "GameInstance/Light_GIS.h"
#include "Components/DirectionalLightComponent.h"

#define DARKFOREST_COLOR FLinearColor(1.0, 0.7, 0.3)
#define FOREST_COLOR FLinearColor(1.0, 1.0, 1.0)

#define DARKFOREST_LIGHT_INTENSITY 50.f
#define FOREST_LIGHT_INTENSITY 500.f

AMyDirectionalLight::AMyDirectionalLight()
{
	PrimaryActorTick.bCanEverTick = true;

	DirectionalLightComponent = CreateDefaultSubobject<UDirectionalLightComponent>(TEXT("DirectionalLightComponent"));
	DirectionalLightComponent->SetLightColor(FColor::White);
	DirectionalLightComponent->SetIntensity(500.f);
	DirectionalLightComponent->SetVisibility(true);  // 라이트가 보이도록 설정
	DirectionalLightComponent->SetActive(true);  // 라이트가 활성화되었는지 확인
	FRotator Rotator = FRotator(-90., 0., 0.);
	DirectionalLightComponent->SetRelativeRotation(Rotator.Quaternion());
}

void AMyDirectionalLight::BeginPlay()
{
	Super::BeginPlay();

	ULight_GIS* Light_GIS = GetGameInstance()->GetSubsystem<ULight_GIS>();
	Light_GIS->RegistDirectionalLight(this);
}

void AMyDirectionalLight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bToDarkForest)
	{
		FLinearColor CurrentLightColor = DirectionalLightComponent->GetLightColor();
		CurrentLightColor = FMath::Lerp(CurrentLightColor, DARKFOREST_COLOR, 0.1f);
		DirectionalLightComponent->SetLightColor(CurrentLightColor);

		float LightIntensity = DirectionalLightComponent->Intensity;
		LightIntensity = FMath::Lerp(LightIntensity, DARKFOREST_LIGHT_INTENSITY, 0.1f);
		DirectionalLightComponent->SetIntensity(LightIntensity);
	}
	else
	{
		FLinearColor CurrentLightColor = DirectionalLightComponent->GetLightColor();
		CurrentLightColor = FMath::Lerp(CurrentLightColor, FOREST_COLOR, 0.1f);
		DirectionalLightComponent->SetLightColor(CurrentLightColor);

		float LightIntensity = DirectionalLightComponent->Intensity;
		LightIntensity = FMath::Lerp(LightIntensity, FOREST_LIGHT_INTENSITY, 0.1f);
		DirectionalLightComponent->SetIntensity(LightIntensity);
	}
}


void AMyDirectionalLight::ToDarkForest()
{
	bToDarkForest = true;
}

void AMyDirectionalLight::ToForest()
{
	bToDarkForest = false;
}

