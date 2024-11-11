// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/TriggerBoxes/ToForestTriggerBox.h"
#include "Misc/Utils.h"
#include "Components/ShapeComponent.h"
#include "Actors/Link/Link.h"
#include "GameInstance/Light_GIS.h"

AToForestTriggerBox::AToForestTriggerBox(const FObjectInitializer& ObjectInitializer)
{
	bGenerateOverlapEventsDuringLevelStreaming = true;

	UShapeComponent* ShapeComponent = GetCollisionComponent();
	ShapeComponent->SetCollisionProfileName(CollisionProfileName::MyTrigger);
	ShapeComponent->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnTrigger);
}

void AToForestTriggerBox::BeginPlay()
{
	Super::BeginPlay();
}

void AToForestTriggerBox::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

void AToForestTriggerBox::Destroyed()
{
	Super::Destroyed();
}

void AToForestTriggerBox::OnTrigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ALink* Link = Cast<ALink>(OtherActor);
	if (!Link) return;
	Link->SetSpotLightActive(false);

	ULight_GIS* GIS = GetGameInstance()->GetSubsystem<ULight_GIS>();
	GIS->SetForest();
}
