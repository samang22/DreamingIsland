// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/NPC/MovingFloorCrane.h"
#include "Components/SplineComponent.h"

#define MFC_MOVING_SPEED 40.f
AMovingFloorCrane::AMovingFloorCrane()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Asset(TEXT("/Script/Engine.StaticMesh'/Game/Assets/Obj/Crane/MovingFloorCrane/MovingFloorCrane.MovingFloorCrane'"));
	check(Asset.Object);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetStaticMesh(Asset.Object);
	RootComponent = StaticMeshComponent;

	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));
	SplineComponent->SetClosedLoop(true);

	SetActorScale3D(FVector(80.0, 80.0, 80.0));
}

void AMovingFloorCrane::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bMove)
	{
		if (bMoveRight)
		{
			// 스플라인을 따라 움직일 거리 업데이트 (예: 초당 100 유닛)
			fDistanceAlongSpline += DeltaTime * MFC_MOVING_SPEED;

			// 스플라인의 길이를 초과하지 않도록 처리
			if (fDistanceAlongSpline > SplineComponent->GetSplineLength())
			{
				bMoveRight = false; // 다시 처음으로
			}
		}
		else
		{
			// 스플라인을 따라 움직일 거리 업데이트 (예: 초당 100 유닛)
			fDistanceAlongSpline -= DeltaTime * MFC_MOVING_SPEED;

			// 스플라인의 길이를 초과하지 않도록 처리
			if (fDistanceAlongSpline < 0.f)
			{
				bMoveRight = true; // 다시 처음으로
			}
		}

	}

	FVector NewLocation = SplineComponent->GetLocationAtDistanceAlongSpline(fDistanceAlongSpline, ESplineCoordinateSpace::World);
	SetActorLocation(NewLocation);
}

void AMovingFloorCrane::BeginPlay()
{
	Super::BeginPlay();
	StaticMeshComponent->RegisterComponent();
	SetActorScale3D(FVector(80.0, 80.0, 80.0));
	bMove = true;
}
