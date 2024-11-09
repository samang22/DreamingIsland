// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/TriggerBoxes/ToDarkForestTriggerBox.h"
#include "Misc/Utils.h"
#include "Components/ShapeComponent.h"
#include "Actors/Link/Link.h"
#include "GameInstance/Light_GIS.h"

AToDarkForestTriggerBox::AToDarkForestTriggerBox(const FObjectInitializer& ObjectInitializer)
{
	bGenerateOverlapEventsDuringLevelStreaming = true;

	UShapeComponent* ShapeComponent = GetCollisionComponent();
	ShapeComponent->SetCollisionProfileName(CollisionProfileName::MyTrigger);
	ShapeComponent->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnTrigger);
}

void AToDarkForestTriggerBox::BeginPlay()
{
	Super::BeginPlay();
}

void AToDarkForestTriggerBox::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

void AToDarkForestTriggerBox::Destroyed()
{
	Super::Destroyed();
}

void AToDarkForestTriggerBox::OnTrigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ALink* Link = Cast<ALink>(OtherActor);
	if (!Link) return;

	ULight_GIS* GIS = GetGameInstance()->GetSubsystem<ULight_GIS>();
	GIS->SetDarkForest();
}
