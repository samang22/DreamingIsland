#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LightBeam.generated.h"

class UMaterialInstanceDynamic;
UCLASS()
class DREAMINGISLAND_API ALightBeam : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALightBeam();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent = nullptr;
	UPROPERTY()
	UMaterialInstanceDynamic* MID = nullptr;
	UPROPERTY()
	double Opacity = 0.0;

protected:
	float SinValue = 0.0;
	bool bIsUp = false;
};
