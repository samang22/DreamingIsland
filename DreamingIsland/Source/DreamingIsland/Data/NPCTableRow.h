// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/StatusComponent/NPCStatusComponent.h"
#include "Misc/Utils.h"
#include "Animation/NPCAnimInstance.h"
#include "AIController.h"

#include "NPCTableRow.generated.h"

USTRUCT()
struct DREAMINGISLAND_API FNPCTableRow : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "NPC")
	USkeletalMesh* SkeletalMesh = nullptr;

	UPROPERTY(EditAnywhere, Category = "NPC")
	FTransform MeshTransform = FTransform::Identity;

	UPROPERTY(EditAnywhere, Category = "NPC|Animation")
	TSubclassOf<UAnimInstance> AnimClass;

public:
	UPROPERTY(EditAnywhere, Category = "NPC|Collision")
	TSubclassOf<UShapeComponent> CollisionClass;
	UPROPERTY(EditAnywhere, Category = "NPC|Collision")
	float CollisionSphereRadius = 32.f;
	UPROPERTY(EditAnywhere, Category = "NPC|Collision")
	FVector CollisionBoxExtent = FVector(32.0, 32.0, 32.0);
	UPROPERTY(EditAnywhere, Category = "NPC|Collision")
	float CollisionCapsuleRadius = 22.f;
	UPROPERTY(EditAnywhere, Category = "NPC|Collision")
	float CollisionCapsuleHalfHeight = 44.f;

public: // To sense link
	UPROPERTY(EditAnywhere, Category = "NPC|SenseLinkCollision")
	TSubclassOf<UShapeComponent> SenseLinkCollisionClass;
	UPROPERTY(EditAnywhere, Category = "NPC|SenseLinkCollision")
	float SenseLinkCollisionSphereRadius = 32.f;
	UPROPERTY(EditAnywhere, Category = "NPC|SenseLinkCollision")
	FVector SenseLinkCollisionBoxExtent = FVector(32.0, 32.0, 32.0);
	UPROPERTY(EditAnywhere, Category = "NPC|SenseLinkCollision")
	float SenseLinkCollisionCapsuleRadius = 22.f;
	UPROPERTY(EditAnywhere, Category = "NPC|SenseLinkCollision")
	float SenseLinkCollisionCapsuleHalfHeight = 44.f;


public: // Movement
	UPROPERTY(EditAnywhere, Category = "NPC|Movement")
	float MovementMaxSpeed = 100.f;
	UPROPERTY(EditAnywhere, Category = "NPC|Movement")
	float RushMovementMaxSpeed = 200.f;



public: // Animation
	UPROPERTY(EditAnywhere, Category = "NPC|Animation")
	UAnimMontage* BeamStMontage;
	UPROPERTY(EditAnywhere, Category = "NPC|Animation")
	UAnimMontage* BeamMontage;
	UPROPERTY(EditAnywhere, Category = "NPC|Animation")
	UAnimMontage* RageMontage;
	UPROPERTY(EditAnywhere, Category = "NPC|Animation")
	UAnimMontage* Action01_Montage;
	UPROPERTY(EditAnywhere, Category = "NPC|Animation")
	UAnimMontage* Action02_Montage;



public: // AI
	UPROPERTY(EditAnywhere, Category = "NPC|AI")
	TSubclassOf<AAIController> AIControllerClass;
};
