// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

struct FItemTableRow;
class UShapeComponent;
class UCharacterMovementComponent;
class ACrane;
UCLASS()
class DREAMINGISLAND_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem(const FObjectInitializer& ObjectInitializer);
	virtual void SetData(const FDataTableRowHandle& InDataTableRowHandle);

protected:
	virtual void PostDuplicate(EDuplicateMode::Type DuplicateMode) override;
	virtual void PostLoad() override;
	virtual void PostLoadSubobjects(FObjectInstancingGraph* OuterInstanceGraph) override;
	virtual void PostInitializeComponents() override;
	virtual void OnConstruction(const FTransform& Transform);
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


protected:
protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> DefaultSceneRoot;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UShapeComponent> CollisionComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

protected:
	UPROPERTY(EditAnywhere)
	FDataTableRowHandle DataTableRowHandle;
	FItemTableRow* ItemData;

protected:
	int ItemValue = 0;

protected:
	UPhysicalMaterial* PhysicalMaterial = nullptr;

public:
	FName GetItemName() const { return DataTableRowHandle.RowName; }
	int GetItemValue() const { return ItemValue; }

protected:
	void ItemCatchedSequence(float DeltaTime);
	bool bIsItemCatched = false;
	AActor* CatchingItemActor = nullptr;
public:
	void SetItemCatched(bool _bIsItemCatched);
	void SetCatchingItemActor(AActor* _CatchingItemActor) { CatchingItemActor = _CatchingItemActor;	}

protected:
	bool bIsPurchased;
public:
	void SetIsPurchased(bool _bIsPurchased) { bIsPurchased = _bIsPurchased; }
	bool GetIsPurchased() const { return bIsPurchased; }

protected:
	ACrane* Magnet = nullptr;
public:
	void SetMagnet(ACrane* _Magnet) { Magnet = _Magnet; }
};
