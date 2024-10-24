// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Monsters/Hinox.h"

AHinox::AHinox(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void AHinox::BeginPlay()
{
	Super::BeginPlay();
	RenderOffWeapon();
	SetWeaponUnEquiped();
}