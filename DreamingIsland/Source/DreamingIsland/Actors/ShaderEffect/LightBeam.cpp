// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/ShaderEffect/LightBeam.h"

#define LIGHTBEAM_OPACITY_MAX 0.2
#define LIGHTBEAM_OPACITY_MIN 0.05

float InterpolateValue(float input)
{
	// Step 1: -1 ~ 1 범위에서 0 ~ 1 범위로 변환
	float normalized = (input + 1) / 2.0f;  // -1 ~ 1 -> 0 ~ 1

	// Step 2: 0 ~ 1 범위에서 0.2 ~ 0.8 범위로 변환
	float output = LIGHTBEAM_OPACITY_MIN + normalized * (LIGHTBEAM_OPACITY_MAX - LIGHTBEAM_OPACITY_MIN); // 0 ~ 1 -> 0.2 ~ 0.8

	return output;
}

ALightBeam::ALightBeam()
{
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BeachMesh(TEXT("/Script/Engine.StaticMesh'/Game/Assets/House/FishingPond/Lightbeam/S_EV_SimpleLightBeam_02.S_EV_SimpleLightBeam_02'"));
	if (BeachMesh.Object)
	{
		StaticMeshComponent->SetStaticMesh(BeachMesh.Object);
	}
	StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	RootComponent = StaticMeshComponent;
}

// Called when the game starts or when spawned
void ALightBeam::BeginPlay()
{
	Super::BeginPlay();
	MID = StaticMeshComponent->CreateDynamicMaterialInstance(0);
	SinValue = FMath::FRandRange(5.f, 10.f);
	MID->SetScalarParameterValue(TEXT("Opacity"), 0.2);
}

void ALightBeam::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SinValue += DeltaTime;
	Opacity = InterpolateValue(FMath::Sin(static_cast<double>(SinValue)));
	MID->SetScalarParameterValue(TEXT("Opacity"), Opacity);
}

