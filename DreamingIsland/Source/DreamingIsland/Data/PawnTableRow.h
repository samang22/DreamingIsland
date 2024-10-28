// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/MonsterStatusComponent.h"
#include "Components/WeaponChildActorComponent.h"
#include "Misc/Utils.h"
#include "Animation/MonsterAnimInstance.h"
#include "AIController.h"

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
	float MovementMaxSpeed = 200.f;
	UPROPERTY(EditAnywhere, Category = "Monster|Movement")
	float RushMovementMaxSpeed = 300.f;



public: // Animation
	UPROPERTY(EditAnywhere, Category = "Monster|Animation")
	UAnimMontage* DamageMontage;
	UPROPERTY(EditAnywhere, Category = "Monster|Animation")
	UAnimMontage* DeadMontage;
	UPROPERTY(EditAnywhere, Category = "Monster|Animation")
	UAnimMontage* AttackMontage;
	UPROPERTY(EditAnywhere, Category = "Monster|Animation")
	UAnimMontage* RushMontage;
	UPROPERTY(EditAnywhere, Category = "Monster|Animation")
	UAnimMontage* FindMontage;
	UPROPERTY(EditAnywhere, Category = "Monster|Animation")
	UAnimMontage* KyoroKyoroMontage;
	UPROPERTY(EditAnywhere, Category = "Monster|Animation")
	UAnimMontage* GuardMontage;
	UPROPERTY(EditAnywhere, Category = "Monster|Animation")
	UAnimMontage* LaughMontage;
	//UPROPERTY(EditAnywhere, Category = "Monster|Animation")
	//UAnimMontage* CatchMontage;
	UPROPERTY(EditAnywhere, Category = "Monster|Animation")
	UAnimMontage* CatchNoMontage;
	UPROPERTY(EditAnywhere, Category = "Monster|Animation")
	UAnimMontage* ThrowMontage;



public: // AI (Only for Enemy)
	UPROPERTY(EditAnywhere, Category = "Monster|AI")
	TSubclassOf<AAIController> AIControllerClass;

//public:
//	UPROPERTY(EditAnywhere, Category = "Monster|Status")
//	TSubclassOf<UMonsterStatusComponent> MonsterStatusClass;

public:
	UPROPERTY(EditAnywhere, Category = "Projectile", meta = (RowType = "ProjectileTableRow"))
	FDataTableRowHandle ProjectileTableRowHandle;

public:
	UPROPERTY(EditAnywhere, Category = "Weapon", meta = (RowType = "WeaponTableRow"))
	FDataTableRowHandle WeaponTableRowHandle;
	UPROPERTY(EditAnywhere, Category = "Weapon")
	bool bUseWeapon = false;
};