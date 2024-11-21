// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/TriggerBoxes/ToToolShopTriggerBox.h"
#include "Components/BoxComponent.h"
#include "Actors/TriggerBoxes/TriggerInterface.h"
#include "Misc/Utils.h"
#include "Actors/Link/Link.h"
#include "Kismet/GameplayStatics.h"
#include "GameInstance/DreamingIsland_GIS.h"
#include "GameInstance/ASyncLoadingScreen_GIS.h"
#include "Blueprint/UserWidget.h"

AToToolShopTriggerBox::AToToolShopTriggerBox(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bGenerateOverlapEventsDuringLevelStreaming = true;
	ActiveCollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("ActiveCollisionComp"));
	ActiveCollisionComponent->SetupAttachment(RootComponent);
	ActiveCollisionComponent->SetCollisionProfileName(CollisionProfileName::MyTrigger);

	UShapeComponent* ShapeComponent = GetCollisionComponent();
	ShapeComponent->SetCollisionProfileName(CollisionProfileName::MyTrigger);
	ShapeComponent->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnTrigger);
	ActiveCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnActivate);
}

void AToToolShopTriggerBox::BeginPlay()
{
	Super::BeginPlay();
}

void AToToolShopTriggerBox::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

void AToToolShopTriggerBox::Destroyed()
{
	Super::Destroyed();
}

void AToToolShopTriggerBox::OnActivate(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ALink* Link = Cast<ALink>(OtherActor);
	if (!Link) return;

	// 1. make Link Go Forward
	Link->SetMoveAuto(true, FVector(0.f, -1.f, 0.f));
}

void AToToolShopTriggerBox::OnTrigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ALink* Link = Cast<ALink>(OtherActor);
	if (!Link) return;
	// Change Level

	Link->SetMoveAuto(false);

	UDreamingIsland_GIS* Subsystem = GetGameInstance()->GetSubsystem<UDreamingIsland_GIS>();
	FVector LinkLocation = Link->GetActorLocation();
	LinkLocation.Y += 100.f;
	Subsystem->SetLinkFieldLocation(LinkLocation);
	Subsystem->SaveLinkData();

	UASyncLoadingScreen_GIS* LoadingScreenSubsystem = GetGameInstance()->GetSubsystem<UASyncLoadingScreen_GIS>();
	UClass* WidgetClass = LoadClass<UUserWidget>(nullptr, TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/UI_Loading.UI_Loading_C'"));
	LoadingScreenSubsystem->ShowLoadingScreen(WidgetClass);

	UGameplayStatics::OpenLevel(GetWorld(), TEXT("ToolShop"));
}
