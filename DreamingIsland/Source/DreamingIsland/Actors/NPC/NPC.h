// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "NPC.generated.h"

#define NPC_AISENSECONFIG_SIGHT_SIGHTRADIUS										500.f
#define NPC_AISENSECONFIG_SIGHT_LOSESIGHTRADIUS									500.f
#define NPC_AISENSECONFIG_SIGHT_LOSESIGHTRADIUS_PERIPHERALVISIONANGLEDEGREES	120.f

enum class NPC_MONTAGE : uint8
{
	BEAM_ST = 0,
	BEAM,
	RAGE,
	ACTION01,
	ACTION02,
	END,
};


class UAdvancedFloatingPawnMovement;
class APatrolPath;
class UNPCStatusComponent;
struct FNPCTableRow;
class UConversationComponent;

UCLASS()
class DREAMINGISLAND_API ANPC : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ANPC(const FObjectInitializer& ObjectInitializer);
	virtual void SetData(const FDataTableRowHandle& InDataTableRowHandle);

protected:
	virtual void PostDuplicate(EDuplicateMode::Type DuplicateMode) override;
	virtual void PostLoad() override;
	virtual void PostLoadSubobjects(FObjectInstancingGraph* OuterInstanceGraph) override;
	// Called when the game starts or when spawned
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected: 
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UShapeComponent> CollisionComponent;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UShapeComponent> SenseLinkCollisionComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;

protected:
	UPROPERTY(VisibleAnywhere)
	class UAIPerceptionComponent* AIPerceptionComponent;

	UPROPERTY(VisibleAnywhere)
	class UAISenseConfig_Sight* AISenseConfig_Sight;

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<APatrolPath> PatrolPathRef;

protected:
	UPROPERTY(VisibleAnywhere)
	UAdvancedFloatingPawnMovement* MovementComponent;

	UPROPERTY(VisibleAnywhere)
	UNPCStatusComponent* StatusComponent;

	UPROPERTY(VisibleAnywhere)
	UConversationComponent* ConversationComponent;

	UPROPERTY(VisibleAnywhere)
	FName NPCName;
public:
	FName GetNPCName() const { return NPCName; }
public:
	UNPCStatusComponent* GetStatusComponent() { return StatusComponent; }
protected:
	UPROPERTY(EditAnywhere)
	FDataTableRowHandle DataTableRowHandle;
	FNPCTableRow* NPCData;

public:
	void SetCollisionProfileName(FName CollisionProfile);
	void SetSenseLinkCollisionProfileName(FName CollisionProfile);

public:
	void PlayMontage(NPC_MONTAGE _InEnum, bool bIsLoop = false);
	bool IsMontage(NPC_MONTAGE _InEnum);
	bool IsPlayingMontage(NPC_MONTAGE _InEnum);

public:
	FVector GetSocketLocation(FName SocketName);

protected:
	bool bIsTalking = false;
	FVector LinkLocation = FVector::Zero();
	FRotator DesiredRotator = FRotator::ZeroRotator;
public:
	void SetIsTalking(bool _bIsTalking, FVector _LinkLocation);
	UFUNCTION()
	void OnConversation(FString Key);
	FString GetScript(FString Key) const;
};
