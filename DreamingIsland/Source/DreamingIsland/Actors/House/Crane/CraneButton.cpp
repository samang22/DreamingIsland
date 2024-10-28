// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/House/Crane/CraneButton.h"
#include "Components/SphereComponent.h"
#include "Animation/AnimInstance.h"
#include "Misc/Utils.h"
#include "Animation/CraneButtonAnimInstance.h"

// Sets default values
ACraneButton::ACraneButton()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> ObjectFinder(TEXT("/Script/Engine.SkeletalMesh'/Game/Assets/Obj/Crane/CraneButton/CraneButton.CraneButton'"));
	check(ObjectFinder.Object);
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	SkeletalMeshComponent->SetSkeletalMesh(ObjectFinder.Object);
	SkeletalMeshComponent->SetAnimClass(UCraneButtonAnimInstance::StaticClass());

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	CollisionComponent->SetCollisionProfileName(CollisionProfileName::SenseLink);
	RootComponent = CollisionComponent;
}

// Called when the game starts or when spawned
void ACraneButton::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACraneButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACraneButton::PlayMontage_ButtonAOn()
{
	UCraneButtonAnimInstance* CraneButtonAnimInstance = Cast<UCraneButtonAnimInstance>(SkeletalMeshComponent->GetAnimInstance());
	CraneButtonAnimInstance->PlayMontage_ButtonAOn();
}

void ACraneButton::PlayMontage_ButtonXOn()
{
	UCraneButtonAnimInstance* CraneButtonAnimInstance = Cast<UCraneButtonAnimInstance>(SkeletalMeshComponent->GetAnimInstance());
	CraneButtonAnimInstance->PlayMontage_ButtonXOn();
}

