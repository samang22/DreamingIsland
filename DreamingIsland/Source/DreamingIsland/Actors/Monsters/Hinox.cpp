// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Monsters/Hinox.h"
#include "Components/HinoxStatusComponent.h"
AHinox::AHinox(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	StatusComponent = CreateDefaultSubobject<UHinoxStatusComponent>(TEXT("HinoxStatusComponent"));
}

void AHinox::BeginPlay()
{
	Super::BeginPlay();
	RenderOffWeapon();
	SetWeaponUnEquiped();
}
