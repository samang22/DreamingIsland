// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
//#include "Actors/Monster.h"
#include "PawnTableRow.generated.h"
/**
 * 
 */

class Monster;
USTRUCT()
struct DREAMINGISLAND_API FPawnTableRow : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "Monster")
	USkeletalMesh* SkeletalMesh = nullptr;

	UPROPERTY(EditAnywhere, Category = "Monster")
	FTransform MeshTransform = FTransform::Identity;

	UPROPERTY(EditAnywhere, Category = "Monster|Animation")
	TSubclassOf<UAnimInstance> AnimClass;

	//UPROPERTY(EditAnywhere, Category = "Monster|Pawn")
	//TSubclassOf<AMonster> PawnClass;

public:
	UPROPERTY(EditAnywhere, Category = "Monster|Collision")
	TSubclassOf<UShapeComponent> CollisionClass/* = USphereComponent::StaticClass()*/;
	UPROPERTY(EditAnywhere, Category = "Monster|Collision")
	float CollisionSphereRadius = 32.f;
	UPROPERTY(EditAnywhere, Category = "Monster|Collision")
	FVector CollisionBoxExtent = FVector(32.0, 32.0, 32.0);
	UPROPERTY(EditAnywhere, Category = "Monster|Collision")
	float CollisionCapsuleRadius = 22.f;
	UPROPERTY(EditAnywhere, Category = "Monster|Collision")
	float CollisionCapsuleHalfHeight = 44.f;

public: // Movement
	UPROPERTY(EditAnywhere, Category = "Monster|Movement")
	float MovementMaxSpeed = 400.f;

public: // Animation
	UPROPERTY(EditAnywhere, Category = "Monster|Animation")
	TArray<UAnimMontage*> HitReactMontage;
	UPROPERTY(EditAnywhere, Category = "Monster|Animation")
	TArray<UAnimMontage*> DieMontage;
};