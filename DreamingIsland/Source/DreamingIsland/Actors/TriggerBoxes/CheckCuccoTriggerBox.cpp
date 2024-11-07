// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/TriggerBoxes/CheckCuccoTriggerBox.h"
#include "Misc/Utils.h"
#include "Components/ShapeComponent.h"
#include "Actors/NPC/Cucco.h"
#include "GameInstance/DreamingIsland_GIS.h"

ACheckCuccoTriggerBox::ACheckCuccoTriggerBox(const FObjectInitializer& ObjectInitializer)
{
	bGenerateOverlapEventsDuringLevelStreaming = true;

	UShapeComponent* ShapeComponent = GetCollisionComponent();
	ShapeComponent->SetCollisionProfileName(CollisionProfileName::MyTrigger);
	ShapeComponent->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnTrigger);

}

void ACheckCuccoTriggerBox::BeginPlay()
{
	Super::BeginPlay();
}

void ACheckCuccoTriggerBox::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

void ACheckCuccoTriggerBox::Destroyed()
{
	Super::Destroyed();
}

void ACheckCuccoTriggerBox::OnTrigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACucco* Cucco = Cast<ACucco>(OtherActor);
	if (!Cucco) return;

	UDreamingIsland_GIS* Subsystem = GetGameInstance()->GetSubsystem<UDreamingIsland_GIS>();
	Subsystem->SetCuccoCount(Subsystem->GetCuccoCount() + 1);
}
