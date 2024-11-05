// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/NPC/CraneFence.h"
#include "Components/SplineComponent.h"

#define CF_MOVING_SPEED 40.f

ACraneFence::ACraneFence()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Asset(TEXT("/Script/Engine.StaticMesh'/Game/Assets/Obj/Crane/CraneFence/CraneFence.CraneFence'"));
	check(Asset.Object);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetStaticMesh(Asset.Object);
	RootComponent = StaticMeshComponent;

	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));
	SplineComponent->SetClosedLoop(false);


	SetActorScale3D(FVector(80.0, 80.0, 80.0));

}

void ACraneFence::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (bMoveUp)
	{
		fDistanceAlongSpline += DeltaTime * CF_MOVING_SPEED;
		if (fDistanceAlongSpline > SplineComponent->GetSplineLength())
		{
			fDistanceAlongSpline = SplineComponent->GetSplineLength();
		}

	}
	else
	{
		fDistanceAlongSpline -= DeltaTime * CF_MOVING_SPEED;
		if (fDistanceAlongSpline < 0.f)
		{
			fDistanceAlongSpline = 0.f;
		}
	}



	FVector NewLocation = SplineComponent->GetLocationAtDistanceAlongSpline(fDistanceAlongSpline, ESplineCoordinateSpace::World);
	SetActorLocation(NewLocation);
}

void ACraneFence::BeginPlay()
{
	Super::BeginPlay();
	StaticMeshComponent->RegisterComponent();
	SetActorScale3D(FVector(80.0, 80.0, 80.0));
	bMoveUp = true;
}
