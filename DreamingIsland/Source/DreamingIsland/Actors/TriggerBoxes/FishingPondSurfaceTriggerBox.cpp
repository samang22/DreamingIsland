// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/TriggerBoxes/FishingPondSurfaceTriggerBox.h"
#include "Components/BoxComponent.h"
#include "Actors/TriggerBoxes/TriggerInterface.h"
#include "Misc/Utils.h"
#include "Actors/Link/FishingLink.h"
#include "Actors/NPC/FishingLure.h"
#include "Actors/Projectile/Projectile.h"
#include "Kismet/GameplayStatics.h"

AFishingPondSurfaceTriggerBox::AFishingPondSurfaceTriggerBox(const FObjectInitializer& ObjectInitializer)
{
	bGenerateOverlapEventsDuringLevelStreaming = true;

	UShapeComponent* ShapeComponent = GetCollisionComponent();
	ShapeComponent->SetCollisionProfileName(CollisionProfileName::MyTrigger);
	ShapeComponent->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnTrigger);
}

void AFishingPondSurfaceTriggerBox::BeginPlay()
{
	Super::BeginPlay();
}

void AFishingPondSurfaceTriggerBox::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

void AFishingPondSurfaceTriggerBox::Destroyed()
{
	Super::Destroyed();
}

void AFishingPondSurfaceTriggerBox::OnTrigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AFishingLure* Lure = Cast<AFishingLure>(OtherActor);
	if (!Lure) return;
	if (!Lure->GetFollowingActor()) return;
	Lure->SetFollowingActor(nullptr);

	AActor* Projectile = Cast<AProjectile>(Lure->GetFollowingActor());
	if (Projectile)	Lure->AddForce(Projectile->GetVelocity() * 1000.f);
}
