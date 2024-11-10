// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/ShaderEffect/MyExponentialHeightFog.h"
#include "Engine/ExponentialHeightFog.h" 
#include "Components/ExponentialHeightFogComponent.h" 
#include "GameInstance/Light_GIS.h"

// Sets default values
AMyExponentialHeightFog::AMyExponentialHeightFog()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HeightFogComponent = CreateDefaultSubobject<UExponentialHeightFogComponent>(TEXT("HeightFogComponent"));
	HeightFogComponent->SetVisibility(false);
}

// Called when the game starts or when spawned
void AMyExponentialHeightFog::BeginPlay()
{
	Super::BeginPlay();
	ULight_GIS* Light_GIS = GetGameInstance()->GetSubsystem<ULight_GIS>();
	Light_GIS->RegistExponentialHeightFog(this);
	HeightFogComponent->SetFogDensity(10.0f);
	HeightFogComponent->SetStartDistance(1000.0f);
	HeightFogComponent->SetFogMaxOpacity(0.8f);
	HeightFogComponent->SetFogHeightFalloff(0.1f);
}

// Called every frame
void AMyExponentialHeightFog::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyExponentialHeightFog::SetHeightFogActive()
{
	HeightFogComponent->SetVisibility(true);
}

void AMyExponentialHeightFog::SetHeightFogDeActive()
{
	HeightFogComponent->SetVisibility(false);
}

