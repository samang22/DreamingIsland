// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/TriggerBoxes/ToCraneGameTriggerBox.h"
#include "Components/BoxComponent.h"
#include "Actors/TriggerBoxes/TriggerInterface.h"
#include "Misc/Utils.h"
#include "Actors/Link/Link.h"
#include "Kismet/GameplayStatics.h"

AToCraneGameTriggerBox::AToCraneGameTriggerBox(const FObjectInitializer& ObjectInitializer)
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

void AToCraneGameTriggerBox::BeginPlay()
{
	Super::BeginPlay();
}

void AToCraneGameTriggerBox::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

void AToCraneGameTriggerBox::Destroyed()
{
	Super::Destroyed();
}

void AToCraneGameTriggerBox::OnActivate(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ALink* Link = Cast<ALink>(OtherActor);
	if (!Link) return;

	// 1. make Link Go Forward
	Link->SetMoveAuto(true, FVector(0.f, -1.f, 0.f));
}

void AToCraneGameTriggerBox::OnTrigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ALink* Link = Cast<ALink>(OtherActor);
	if (!Link) return;
	// Change Level

	Link->SetMoveAuto(false);
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("CraneGame"));
}
