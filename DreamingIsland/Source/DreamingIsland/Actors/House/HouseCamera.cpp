// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/House/HouseCamera.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Actors/Link/LinkController.h"
#include "Actors/NPC/ToolShopKeeper.h"

#define LINK_LEFT_OFFSET 200.f
#define LINK_FORWARD_OFFSET -40.f
#define LINK_UP_OFFSET 50.f

#define TSK_FORWARD_OFFSET 130.f
#define TSK_UP_OFFSET 50.f

#define LINK_ITEM_GET_FORWARD_OFFSET 150.f
#define LINK_ITEM_GET_UP_OFFSET 150.f

#define DEFAULT_HOUSE_CAMERA_POSITION FVector(-140.0, 530.0, 810.0)


#define DEFAULT_HOUSE_CAMERA_ROTATION FRotator(-50., -89.99, 0)

#define HOUSE_CAMERA_CONVERSATION_LERP_ALPHA 0.03f
#define HOUSE_CAMERA_ITEM_GET_LERP_ALPHA 0.1f



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
	LinkController->OnLinkItemGet.AddDynamic(this, &ThisClass::OnLinkItemGet);
	LinkController->OnLinkItemGetEnd.AddDynamic(this, &ThisClass::OnLinkItemGetEnded);
	// @TODO : do this same in field level


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
	CurrentLocation = FMath::Lerp(CurrentLocation, DesiredLocation, HOUSE_CAMERA_ITEM_GET_LERP_ALPHA);
	SetActorLocation(CurrentLocation);

	FRotator CurrentRotator = GetActorRotation();
	CurrentRotator = FMath::Lerp(CurrentRotator, DesiredRotator, HOUSE_CAMERA_ITEM_GET_LERP_ALPHA);
	SetActorRotation(CurrentRotator);
}

void AHouseCamera::OnLinkTalk(FVector LinkLocation, FVector LinkLeftVector, FVector LinkForwardVector)
{
	FVector TempLocation = LinkLocation;
	TempLocation += LinkLeftVector * LINK_LEFT_OFFSET;
	TempLocation += LinkForwardVector * LINK_FORWARD_OFFSET;
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

void AHouseCamera::OnLinkCaught(FVector TSKLocation, FVector ForwardVector)
{
	FVector TempLocation = TSKLocation;
	TempLocation += ForwardVector * TSK_FORWARD_OFFSET;
	TempLocation += FVector(0., 0., 1.) * TSK_UP_OFFSET;
	DesiredLocation = TempLocation;

	FVector LinkRightVector = TSKLocation * -1;
	FVector NewVector = TSKLocation - DesiredLocation;
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

void AHouseCamera::OnLinkItemGet(FVector LinkLocation, FVector ForwardVector)
{
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

void AHouseCamera::OnLinkItemGetEnded()
{
	DesiredLocation = DefaultLocation;
	DesiredRotator = DefaultRotator;
}

void AHouseCamera::OnMad(FVector TSKLocation, FVector ForwardVector)
{
	FVector TempLocation = TSKLocation;
	TempLocation += ForwardVector * TSK_FORWARD_OFFSET;
	TempLocation += FVector(0., 0., 1.) * TSK_UP_OFFSET;
	DesiredLocation = TempLocation;

	FVector LinkRightVector = TSKLocation * -1;
	FVector NewVector = TSKLocation - DesiredLocation;
	NewVector.Normalize();

	float Pitch = FMath::Asin(NewVector.Z) * (180.0f / PI);
	float Yaw = FMath::Atan2(NewVector.Y, NewVector.X) * (180.0f / PI);
	DesiredRotator = FRotator(Pitch, Yaw, 0.f);
}

void AHouseCamera::OnMadEnd()
{
	DesiredLocation = DefaultLocation;
	DesiredRotator = DefaultRotator;
}

void AHouseCamera::SetTSKDelgateBind(AToolShopKeeper* _Keeper)
{
	ToolShopKeeper = _Keeper;
	ToolShopKeeper->OnLinkCaught.AddDynamic(this, &ThisClass::OnLinkCaught);
	ToolShopKeeper->OnLinkCaughtEnd.AddDynamic(this, &ThisClass::OnLinkCaughtEnd);
	ToolShopKeeper->OnMad.AddDynamic(this, &ThisClass::OnMad);
	ToolShopKeeper->OnMadEnd.AddDynamic(this, &ThisClass::OnMadEnd);
}

