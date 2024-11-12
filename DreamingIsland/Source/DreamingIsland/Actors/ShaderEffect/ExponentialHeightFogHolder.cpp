// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/ShaderEffect/ExponentialHeightFogHolder.h"
#include "Engine/ExponentialHeightFog.h" 
#include "Components/ExponentialHeightFogComponent.h" 
#include "GameInstance/Light_GIS.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AExponentialHeightFogHolder::AExponentialHeightFogHolder()
{
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AExponentialHeightFogHolder::BeginPlay()
{
	Super::BeginPlay();

	ULight_GIS* Light_GIS = GetGameInstance()->GetSubsystem<ULight_GIS>();
	Light_GIS->RegistExponentialHeightFogHolder(this);

	AExponentialHeightFog* tempHeightFog = Cast<AExponentialHeightFog>(UGameplayStatics::GetActorOfClass(GetWorld(), AExponentialHeightFog::StaticClass()));
	if (tempHeightFog)
	{
		HeightFog = tempHeightFog;
	}
}

// Called every frame
void AExponentialHeightFogHolder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HeightFog)
	{
		float CurrentDensity = HeightFog->GetComponent()->FogDensity;
		CurrentDensity = FMath::Lerp(CurrentDensity, GoalFogDensity, 0.01f);
		HeightFog->GetComponent()->SetFogDensity(CurrentDensity);
	}

}

