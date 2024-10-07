// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster.h"

UMonsterDataAsset::UMonsterDataAsset()
{
}


// Sets default values
AMonster::AMonster()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//static ConstructorHelpers::FObjectFinder<USkeletalMesh> ObjectFinder(TEXT("/Script/Engine.SkeletalMesh'/Game/Resources/ControlRig/Characters/Mannequins/Meshes/SKM_Manny.SKM_Manny'"));
	//check(ObjectFinder.Object);
	//SkeletalMesh = ObjectFinder.Object;
}

// Called when the game starts or when spawned
void AMonster::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


