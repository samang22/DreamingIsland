// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/House/FishingPondCamera.h"
#include "Actors/Link/FishingLinkController.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"

#define DEFAULT_FISHINGPOND_CAMERA_POSITION			FVector(-420.0, 2800.0, 550.0)
#define DEFAULT_FISHINGPOND_CAMERA_ROTATION			FRotator(0., -89.99, 0)

#define FISHINGPOND_CAMERA_ORTHO_WIDTH				2250.f

#define FISHINGPOND_CAMERA_MOVE_LERP				0.1f
#define FISHINGPOND_CAMERA_ROTATE_LERP				0.1f


AFishingPondCamera::AFishingPondCamera()
{
	PrimaryActorTick.bCanEverTick = true;
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
}

void AFishingPondCamera::BeginPlay()
{
	Super::BeginPlay();
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (AFishingLinkController* LinkController = Cast<AFishingLinkController>(PlayerController))
	{
		LinkController->SetViewTarget(this);
	}

	DefaultLocation = DEFAULT_FISHINGPOND_CAMERA_POSITION;
	DefaultRotator = DEFAULT_FISHINGPOND_CAMERA_ROTATION;
	DesiredLocation = DefaultLocation;
	DesiredRotator = DefaultRotator;

	if (Camera)
	{
		Camera->ProjectionMode = ECameraProjectionMode::Orthographic;
		Camera->OrthoWidth = FISHINGPOND_CAMERA_ORTHO_WIDTH;  // 원하는 직교 투영의 크기로 설정
	}
}

// Called every frame
void AFishingPondCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector CurrentLocation = GetActorLocation();
	CurrentLocation = FMath::Lerp(CurrentLocation, DesiredLocation, FISHINGPOND_CAMERA_MOVE_LERP);
	SetActorLocation(CurrentLocation);

	FRotator CurrentRotator = GetActorRotation();
	CurrentRotator = FMath::Lerp(CurrentRotator, DesiredRotator, FISHINGPOND_CAMERA_ROTATE_LERP);
	SetActorRotation(CurrentRotator);
}

void AFishingPondCamera::OnLinkCatch(FVector LinkLocation)
{
}

