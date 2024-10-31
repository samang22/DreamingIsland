// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/House/HouseCamera.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Actors/Link/LinkController.h"

#define LINK_LEFT_OFFSET 200.f
#define LINK_FOWARD_OFFSET -40.f
#define LINK_UP_OFFSET 50.f

#define TSK_FOWARD_OFFSET -40.f
#define TSK_UP_OFFSET 50.f

#define DEFAULT_HOUSE_CAMERA_POSITION FVector(0., 670., 730.)
#define DEFAULT_HOUSE_CAMERA_ROTATION FRotator(-50., -89.99, 0)

// Sets default values
AHouseCamera::AHouseCamera()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
}

// Called when the game starts or when spawned
void AHouseCamera::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	ALinkController* LinkController = Cast<ALinkController>(PlayerController);

	LinkController->SetViewTarget(this);
	LinkController->OnLinkTalk.AddDynamic(this, &ThisClass::OnLinkTalk);
	LinkController->OnLinkTalkEnd.AddDynamic(this, &ThisClass::OnLinkTalkEnd);
	LinkController->OnLinkCaught.AddDynamic(this, &ThisClass::OnLinkCaught);
	LinkController->OnLinkCaughtEnd.AddDynamic(this, &ThisClass::OnLinkCaughtEnd);

	DefaultLocation = DEFAULT_HOUSE_CAMERA_POSITION;
	DefaultRotator = DEFAULT_HOUSE_CAMERA_ROTATION;
	DesiredLocation = DefaultLocation;
	DesiredRotator = DefaultRotator;
}

// Called every frame
void AHouseCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector CurrentLocation = GetActorLocation();
	CurrentLocation = FMath::Lerp(CurrentLocation, DesiredLocation, 0.03f);
	SetActorLocation(CurrentLocation);

	FRotator CurrentRotator = GetActorRotation();
	CurrentRotator = FMath::Lerp(CurrentRotator, DesiredRotator, 0.03f);
	SetActorRotation(CurrentRotator);
}

void AHouseCamera::OnLinkTalk(FVector LinkLocation, FVector LinkLeftVector, FVector LinkForwardVector)
{
	FVector TempLocation = LinkLocation;
	TempLocation += LinkLeftVector * LINK_LEFT_OFFSET;
	TempLocation += LinkForwardVector * LINK_FOWARD_OFFSET;
	TempLocation += FVector(0., 0., 1.) * LINK_UP_OFFSET;
	DesiredLocation = TempLocation;

	FVector LinkRightVector = LinkLeftVector * -1;
	FVector NewVector = LinkRightVector + LinkForwardVector + FVector(0., 0., -0.2);
	NewVector.Normalize();



	float Pitch = FMath::Asin(NewVector.Z) * (180.0f / PI);
	float Yaw = FMath::Atan2(NewVector.Y, NewVector.X) * (180.0f / PI);
	DesiredRotator = FRotator(Pitch, Yaw, 0.f);
}

void AHouseCamera::OnLinkTalkEnd()
{
	DesiredLocation = DefaultLocation;
	DesiredRotator = DefaultRotator;
}

void AHouseCamera::OnLinkCaught(FVector TSKLocation)
{
	FVector TempLocation = TSKLocation;
	TempLocation += FVector(0., 1., 0.) * TSK_FOWARD_OFFSET;
	TempLocation += FVector(0., 0., 1.) * TSK_UP_OFFSET;
	DesiredLocation = TempLocation;

	FVector LinkRightVector = TSKLocation * -1;
	FVector NewVector = DesiredLocation - TSKLocation;
	NewVector.Normalize();

	float Pitch = FMath::Asin(NewVector.Z) * (180.0f / PI);
	float Yaw = FMath::Atan2(NewVector.Y, NewVector.X) * (180.0f / PI);
	DesiredRotator = FRotator(Pitch, Yaw, 0.f);
}

void AHouseCamera::OnLinkCaughtEnd()
{
	DesiredLocation = DefaultLocation;
	DesiredRotator = DefaultRotator;
}

