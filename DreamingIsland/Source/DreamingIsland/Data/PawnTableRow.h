// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PawnTableRow.generated.h"
/**
 * 
 */
USTRUCT()
struct DREAMINGISLAND_API FPawnTableRow : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "Enemy")
	USkeletalMesh* SkeletalMesh = nullptr;

	UPROPERTY(EditAnywhere, Category = "Enemy")
	FTransform MeshTransform = FTransform::Identity;

	UPROPERTY(EditAnywhere, Category = "Enemy|Animation")
	TSubclassOf<UAnimInstance> AnimClass;

public:
	UPROPERTY(EditAnywhere, Category = "Enemy|Collision")
	TSubclassOf<UShapeComponent> CollisionClass/* = USphereComponent::StaticClass()*/;
	UPROPERTY(EditAnywhere, Category = "Enemy|Collision")
	float CollisionSphereRadius = 32.f;
	UPROPERTY(EditAnywhere, Category = "Enemy|Collision")
	FVector CollisionBoxExtent = FVector(32.0, 32.0, 32.0);
	UPROPERTY(EditAnywhere, Category = "Enemy|Collision")
	float CollisionCapsuleRadius = 22.f;
	UPROPERTY(EditAnywhere, Category = "Enemy|Collision")
	float CollisionCapsuleHalfHeight = 44.f;

public: // Animation
	UPROPERTY(EditAnywhere, Category = "Enemy|Animation")
	TArray<UAnimMontage*> HitReactMontage;
	UPROPERTY(EditAnywhere, Category = "Enemy|Animation")
	TArray<UAnimMontage*> DieMontage;
};