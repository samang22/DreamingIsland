// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Link/FishingLinkController.h"
#include "Actors/Link/LinkCameraManager.h"
#include "Components/StatusComponent/FishingLinkStatusComponent.h"
#include "Animation/FishingLinkAnimInstance.h"
#include "Actors/Link/FishingLink.h"
#include "Actors/NPC/FishingLure.h"


AFishingLinkController::AFishingLinkController()
{
	{
		static ConstructorHelpers::FObjectFinder<UInputMappingContext> Asset
		{ TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Blueprint/Link/InputAction/IMC_Link.IMC_Link'") };
		check(Asset.Object);

		IMC_Default = Asset.Object;
	}
	PlayerCameraManagerClass = ALinkCameraManager::StaticClass();
}

void AFishingLinkController::BeginPlay()
{
	Super::BeginPlay();

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	Subsystem->AddMappingContext(IMC_Default, 0);
}

void AFishingLinkController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	ensure(EnhancedInputComponent);

	if (const UInputAction* InputAction = FUtils::GetInputActionFromName(IMC_Default, TEXT("IA_Walk")))
	{
		EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Triggered, this, &ThisClass::OnMove);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("IA_Walk is disabled"));
	}

	if (const UInputAction* InputAction = FUtils::GetInputActionFromName(IMC_Default, TEXT("IA_Attack")))
	{
		EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Completed, this, &ThisClass::OnThrow);
		EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Triggered, this, &ThisClass::OnPull);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("IA_Attack is disabled"));
	}

	if (const UInputAction* InputAction = FUtils::GetInputActionFromName(IMC_Default, TEXT("IA_Interact")))
	{
		EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Started, this, &ThisClass::OnShake);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("IA_Interact is disabled"));
	}
}

void AFishingLinkController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	StatusComponent = InPawn->GetComponentByClass<UFishingLinkStatusComponent>();
	check(StatusComponent);

	USkeletalMeshComponent* SkeletalMeshComponent = InPawn->GetComponentByClass<USkeletalMeshComponent>();
	AnimInstance = Cast<UFishingLinkAnimInstance>(SkeletalMeshComponent->GetAnimInstance());
	check(AnimInstance);
}

void AFishingLinkController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFishingLinkController::OnMove(const FInputActionValue& InputActionValue)
{
	if (FISHINGLINK_STATUS::FISHING != StatusComponent->GetFishingLinkStatus()) return;

	const FVector ForwardVector = FVector(0.0, 0.0, 1.0);
	const FVector RightVector = FVector(1.0, 0.0, 0.0);
	const FVector2D ActionValue = InputActionValue.Get<FVector2D>();

	AFishingLure* FishingLure = Cast<AFishingLink>(GetPawn())->GetFishingLure();
	if (FishingLure)
	{
		FishingLure->Move(RightVector, ActionValue.X);
		FishingLure->Move(ForwardVector, -1.0 * ActionValue.Y);
	}
}

void AFishingLinkController::OnThrow(const FInputActionValue& InputActionValue)
{
	AFishingLink* Link = Cast<AFishingLink>(GetPawn());
	if (FISHINGLINK_STATUS::IDLE == StatusComponent->GetFishingLinkStatus())
	{
		Link->PlayMontage(FISHINGLINK_MONTAGE::THROW_LURE);
	}
}

void AFishingLinkController::OnPull(const FInputActionValue& InputActionValue)
{
	AFishingLink* Link = Cast<AFishingLink>(GetPawn());
	if (FISHINGLINK_STATUS::FISHING == StatusComponent->GetFishingLinkStatus())
	{
		StatusComponent->SetFishingLinkStatus(FISHINGLINK_STATUS::PULLING);
	}

	if (FISHINGLINK_STATUS::PULLING == StatusComponent->GetFishingLinkStatus())
	{
		Link->GetFishingLure()->PullFish();
		Link->PullLure();
	}
}

void AFishingLinkController::OnShake(const FInputActionValue& InputActionValue)
{
}

