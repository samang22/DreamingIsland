// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/LinkController.h"
#include "LinkController.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/Character.h"
#include "Components/SoftWheelSpringArmComponent.h"
#include "Components/LinkStatusComponent.h"
#include "Actors/LinkCameraManager.h"
#include "Actors/Link.h"


ALinkController::ALinkController()
{
	{
		static ConstructorHelpers::FObjectFinder<UInputMappingContext> Asset
		{ TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Blueprint/Link/InputAction/IMC_Link.IMC_Link'") };
		check(Asset.Object);

		IMC_Default = Asset.Object;
	}
	PlayerCameraManagerClass = ALinkCameraManager::StaticClass();
}

void ALinkController::BeginPlay()
{
	Super::BeginPlay();

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	Subsystem->AddMappingContext(IMC_Default, 0);
}

void ALinkController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	ensure(EnhancedInputComponent);

	if (const UInputAction* InputAction = FUtils::GetInputActionFromName(IMC_Default, TEXT("IA_Walk")))
	{
		EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Triggered, this, &ThisClass::OnWalk);
		EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Completed, this, &ThisClass::OnWalkOff);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("IA_Walk is disabled"));
	}

	if (const UInputAction* InputAction = FUtils::GetInputActionFromName(IMC_Default, TEXT("IA_Run")))
	{
		EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Triggered, this, &ThisClass::OnRun);
		EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Completed, this, &ThisClass::OnRunOff);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("IA_Run is disabled"));
	}

	if (const UInputAction* InputAction = FUtils::GetInputActionFromName(IMC_Default, TEXT("IA_Interact")))
	{
		EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Triggered, this, &ThisClass::OnInteract);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("IA_Interact is disabled"));
	}

	if (bZoomWheel)
	{
		if (const UInputAction* InputAction = FUtils::GetInputActionFromName(IMC_Default, TEXT("IA_ZoomWheel")))
		{
			EnhancedInputComponent->BindAction(InputAction,
				ETriggerEvent::Triggered, this, &ThisClass::OnZoomWheel);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("IA_ZoomWheel is disabled"));
		}
	}
}

void ALinkController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	StatusComponent = InPawn->GetComponentByClass<ULinkStatusComponent>();
	check(StatusComponent);
}

void ALinkController::OnWalk(const FInputActionValue& InputActionValue)
{
	StatusComponent->SetOnAnimationStatus(LINK_BIT_WALK);

	const FVector2D ActionValue = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = K2_GetActorRotation();
	const FRotator RotationYaw = FRotator(0.0, Rotation.Yaw, 0.0);
	const FVector ForwardVector = FVector(1.0, 0.0, 0.0);
	const FVector RightVector = FVector(0.0, 1.0, 0.0);

	APawn* ControlledPawn = GetPawn();
	if (bRun)
	{
		ControlledPawn->AddMovementInput(ForwardVector, ActionValue.X);
		ControlledPawn->AddMovementInput(RightVector, ActionValue.Y);
	}
	else
	{
		ControlledPawn->AddMovementInput(ForwardVector, ActionValue.X);
		ControlledPawn->AddMovementInput(RightVector, ActionValue.Y);
	}
}

void ALinkController::OnWalkOff(const FInputActionValue& InputActionValue)
{
	StatusComponent->SetOffAnimationStatus(LINK_BIT_WALK);
}

void ALinkController::OnRun(const FInputActionValue& InputActionValue)
{
	bRun = true;
	StatusComponent->SetOnAnimationStatus(LINK_BIT_RUN);
	Cast<ALink>(GetPawn())->SetSpeedRun();
}

void ALinkController::OnRunOff(const FInputActionValue& InputActionValue)
{
	bRun = false;
	StatusComponent->SetOffAnimationStatus(LINK_BIT_RUN);
	Cast<ALink>(GetPawn())->SetSpeedWalk();
}

void ALinkController::OnAttack(const FInputActionValue& InputActionValue)
{
}

void ALinkController::OnInteract(const FInputActionValue& InputActionValue)
{
}

void ALinkController::OnZoomWheel(const FInputActionValue& InputActionValue)
{
}
