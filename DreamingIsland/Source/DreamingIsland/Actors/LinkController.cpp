// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/LinkController.h"
#include "LinkController.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/Character.h"
#include "Components/SoftWheelSpringArmComponent.h"
#include "Components/LinkStatusComponent.h"
#include "Actors/LinkCameraManager.h"
#include "Actors/Link.h"
#include "Animation/LinkAnimInstance.h"
#include "Actors/Default/DefaultHUD.h"
#include "Actors/NPC/NPC.h"

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

	if (const UInputAction* InputAction = FUtils::GetInputActionFromName(IMC_Default, TEXT("IA_Attack")))
	{
		EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Triggered, this, &ThisClass::OnAttack);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("IA_Attack is disabled"));
	}

	if (const UInputAction* InputAction = FUtils::GetInputActionFromName(IMC_Default, TEXT("IA_Interact")))
	{
		EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Triggered, this, &ThisClass::OnInteract);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("IA_Interact is disabled"));
	}

	if (const UInputAction* InputAction = FUtils::GetInputActionFromName(IMC_Default, TEXT("IA_Lay")))
	{
		EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Triggered, this, &ThisClass::OnLay);
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

	USkeletalMeshComponent* SkeletalMeshComponent = InPawn->GetComponentByClass<USkeletalMeshComponent>();
	AnimInstance = Cast<ULinkAnimInstance>(SkeletalMeshComponent->GetAnimInstance());
	check(AnimInstance);

	{
		AnimInstance->OnMontageEnded.AddDynamic(this, &ThisClass::OnSlashAttackMontageEnd);
	}
}

void ALinkController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const bool bMontagePlaying = AnimInstance->IsAnyMontagePlaying();

	if (bMontagePlaying)
	{
		//Movement
	}

	MoveAutoSequence(DeltaTime);
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
	AnimInstance->PlayAttackMontage();
}

void ALinkController::OnInteract(const FInputActionValue& InputActionValue)
{
	ALink* Link = Cast<ALink>(GetPawn());

	if (Link->IsOverlappedNPC())
	{
		// @TODO
		
		OnLinkTalk.Broadcast(Link->GetActorLocation(), -1 * Link->GetActorRightVector(), Link->GetActorForwardVector());
		ADefaultHUD* DefaultHUD = Cast<ADefaultHUD>(GetHUD());
		
		const ANPC* NPC = Cast<ANPC>(Link->GetOverlappedNPC());
		FString Script = NPC->GetScript(TEXT("Greeting"));
		DefaultHUD->OnSetStringToConversation(NPC->GetNPCName().ToString(), Script);

		return;
		// 4. Conversation blah blah
	}
	else if (Link->IsOverlappedItem()
		&& !Link->IsCatchingItem()
		)
	{
		AnimInstance->PlayItemCarryMontage();
		Link->CatchItem();
	}
	 
}

void ALinkController::OnLay(const FInputActionValue& InputActionValue)
{
	ALink* Link = Cast<ALink>(GetPawn());

	if (Link->IsOverlappedNPC())
	{
		OnLinkTalkEnd.Broadcast();
		return;
	}

	if (Link->IsCatchingItem()
	&& !Link->IsPlayingMontage(LINK_MONTAGE::END))
	{
		Link->LayItem();
	}


}

void ALinkController::OnZoomWheel(const FInputActionValue& InputActionValue)
{
}

void ALinkController::OnSlashAttackMontageEnd(UAnimMontage* Montage, bool bInterrupted)
{
}

void ALinkController::MoveAutoSequence(float DeltaTime)
{
	if (bIsMoveAuto)
	{
		APawn* ControlledPawn = GetPawn();
		if (ControlledPawn)
		{
			ControlledPawn->AddMovementInput(MoveAutoDirection, 1);
			StatusComponent->SetOnAnimationStatus(LINK_BIT_WALK);
		}
	}
}

void ALinkController::SetMoveAuto(bool bFlag, FVector Direction)
{
	bIsMoveAuto = bFlag;
	MoveAutoDirection = Direction;
}

