// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/House/FishingPondCamera.h"
#include "Actors/Link/FishingLinkController.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "Misc/Utils.h"
#include "Actors/Link/FishingLink.h"

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

	ACharacter* Character = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (AFishingLink* Link = Cast<AFishingLink>(Character))
	{
		Link->OnLinkFishGet.AddDynamic(this, &ThisClass::OnLinkFishGet);
		Link->OnLinkFishGetEnd.AddDynamic(this, &ThisClass::OnLinkFishGetEnd);
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

void AFishingPondCamera::OnLinkFishGet(FVector LinkLocation, FVector ForwardVector)
{
	if (Camera)
	{
		Camera->ProjectionMode = ECameraProjectionMode::Perspective;
	}

	FVector tempLocation = LinkLocation;
	tempLocation += ForwardVector * LINK_ITEM_GET_FORWARD_OFFSET;
	tempLocation += FVector(0., 0., 1.) * LINK_ITEM_GET_UP_OFFSET;

	DesiredLocation = tempLocation;

	FVector NewVector = LinkLocation - DesiredLocation;
	NewVector.Normalize();

	float Pitch = FMath::Asin(NewVector.Z) * (180.0f / PI);
	float Yaw = FMath::Atan2(NewVector.Y, NewVector.X) * (180.0f / PI);
	DesiredRotator = FRotator(Pitch, Yaw, 0.f);
}

void AFishingPondCamera::OnLinkFishGetEnd()
{
	if (Camera)
	{
		Camera->ProjectionMode = ECameraProjectionMode::Orthographic;
		Camera->OrthoWidth = FISHINGPOND_CAMERA_ORTHO_WIDTH; 
	}

	DesiredLocation = DefaultLocation;
	DesiredRotator = DefaultRotator;
}