// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Link/LinkController.h"
#include "LinkController.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/Character.h"
#include "Components/SoftWheelSpringArmComponent.h"
#include "Components/StatusComponent/LinkStatusComponent.h"
#include "Actors/Link/LinkCameraManager.h"
#include "Actors/Link/Link.h"
#include "Animation/LinkAnimInstance.h"
#include "Actors/Default/DefaultHUD.h"
#include "Actors/NPC/NPC.h"
#include "Actors/Items/Item.h"
#include "Kismet/GameplayStatics.h"

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
		EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Triggered, this, &ThisClass::OnChoose);
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
		EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Completed, this, &ThisClass::OnCheck);
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
		UE_LOG(LogTemp, Warning, TEXT("IA_Lay is disabled"));
	}

	if (const UInputAction* InputAction = FUtils::GetInputActionFromName(IMC_Default, TEXT("IA_Get")))
	{
		EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Completed, this, &ThisClass::OnGet);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("IA_Get is disabled"));
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

	ADefaultHUD* DefaultHUD = Cast<ADefaultHUD>(GetHUD());
	if (DefaultHUD)
	{
		DefaultHUD->OnSetRupeeNum(StatusComponent->GetRupee());
	}
}

void ALinkController::OnWalk(const FInputActionValue& InputActionValue)
{
	if (StatusComponent->GetIsConversation()) return;

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
	if (StatusComponent->GetIsConversation()) return;
	Cast<ALink>(GetPawn())->PlayMontage(LINK_MONTAGE::SLASH);
}

void ALinkController::OnInteract(const FInputActionValue& InputActionValue)
{
	ALink* Link = Cast<ALink>(GetPawn());

	if (Link->IsOverlappedNPC())
	{
		// @TODO
		
		OnLinkTalk.Broadcast(Link->GetActorLocation(), -1 * Link->GetActorRightVector(), Link->GetActorForwardVector());
		StatusComponent->SetIsConversation(true);

		ADefaultHUD* DefaultHUD = Cast<ADefaultHUD>(GetHUD());
		
		const ANPC* NPC = Cast<ANPC>(Link->GetOverlappedNPC());

		if (Link->IsCatchingItem())
		{
			const AItem* Item = Cast<AItem>(Link->GetCatchingItem());
			FString ItemName = Item->GetItemName().ToString();
			FString Script1 = NPC->GetScript(TEXT("Buy1")); // 은
			FString ItemValue = FString::FormatAsNumber(Item->GetItemValue());
			FString Script2 = NPC->GetScript(TEXT("Buy2")); // 루피입니다!
			FString Result = ItemName + Script1 + ItemValue + Script2;
			DefaultHUD->OnSetStringToConversation(NPC->GetNPCName().ToString(), Result);
			DefaultHUD->OnShowConversationWidget();
			DefaultHUD->OnShowRupeeWidget();
			DefaultHUD->OnShowChooseWidget();

		}
		else if (!Link->IsCatchingItem())
		{
			FString Script = NPC->GetScript(TEXT("Greeting"));
			DefaultHUD->OnSetStringToConversation(NPC->GetNPCName().ToString(), Script);
			DefaultHUD->OnShowConversationWidget();
		}


	}
	else if (Link->IsOverlappedItem()
		&& !Link->IsCatchingItem()
		)
	{
		AnimInstance->PlayMontage(LINK_MONTAGE::ITEM_CARRY);
		Link->CatchItem();
	}
	 
}

void ALinkController::OnLay(const FInputActionValue& InputActionValue)
{
	ALink* Link = Cast<ALink>(GetPawn());

	if (Link->IsOverlappedNPC())
	{
		OnLinkTalkEnd.Broadcast();
		StatusComponent->SetIsConversation(false);
		ADefaultHUD* DefaultHUD = Cast<ADefaultHUD>(GetHUD());
		DefaultHUD->OnHideChooseWidget();
		DefaultHUD->OnHideConversationWidget();
		DefaultHUD->OnHideRupeeWidget();
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

void ALinkController::OnChoose(const FInputActionValue& InputActionValue)
{
	if (!StatusComponent->GetIsConversation()) return;

	const FVector2D ActionValue = InputActionValue.Get<FVector2D>();
	ADefaultHUD* DefaultHUD = Cast<ADefaultHUD>(GetHUD());
	DefaultHUD->OnSetSelection(ActionValue.Y < 0 ? true : false);
}

void ALinkController::OnCheck(const FInputActionValue& InputActionValue)
{
	if (!StatusComponent->GetIsConversation()) return;

	ADefaultHUD* DefaultHUD = Cast<ADefaultHUD>(GetHUD());
	if (!DefaultHUD->GetIsChooseWidgetVisible()) return;



	if (DefaultHUD->GetSelection())
	{
		// now check which one is talking with
		ALink* Link = Cast<ALink>(GetPawn());
		const AActor* OverlappedNPC = Link->GetOverlappedNPC();
		const ANPC* NPC = Cast<ANPC>(OverlappedNPC);
		if (NPC_Name_Korean::ToolShopKeeper == NPC->GetNPCName())
		{
			AItem* Item = Cast<AItem>(Link->GetCatchingItem());
			if (StatusComponent->GetRupee() >= Item->GetItemValue())
			{
				StatusComponent->AddRupee(Item->GetItemValue() * -1);
				DefaultHUD->OnSetStringToConversation(NPC->GetNPCName().ToString(), NPC->GetScript(TSK_ConversationKey::BuySucceeded));
				DefaultHUD->OnHideChooseWidget();
				Item->SetIsPurchased(true);
			}
			else
			{
				DefaultHUD->OnSetStringToConversation(NPC->GetNPCName().ToString(), NPC->GetScript(TSK_ConversationKey::BuyFailed));
				DefaultHUD->OnHideChooseWidget();
			}
		}
	}
	else
	{
		OnLinkTalkEnd.Broadcast();
		StatusComponent->SetIsConversation(false);
		DefaultHUD->OnHideChooseWidget();
		DefaultHUD->OnHideConversationWidget();
		DefaultHUD->OnHideRupeeWidget();
	}

}

void ALinkController::OnGet(const FInputActionValue& InputActionValue)
{
	ALink* Link = Cast<ALink>(GetPawn());
	if (Link->IsCatchingItem())
	{
		AItem* Item = Cast<AItem>(Link->GetCatchingItem());
		Link->SetIsThief(!Item->GetIsPurchased());
		FName ItemName = Item->GetItemName();

		if (Item_Name::Bomb == ItemName)
		{
			StatusComponent->AddBomb(1);
		}
		else if (Item_Name::Arrow == ItemName)
		{
			StatusComponent->AddArrow(1);
		}
		else if (Item_Name::Bow == ItemName)
		{
			StatusComponent->SetOnToolEquipStatus(LINK_TOOL_BIT_BOW);
		}
		else if (Item_Name::Shield == ItemName)
		{
			StatusComponent->SetOnToolEquipStatus(LINK_TOOL_BIT_SHIELD);
		}
		else if (Item_Name::Sword == ItemName)
		{
			StatusComponent->SetOnToolEquipStatus(LINK_TOOL_BIT_SWORD);
		}
		// @TODO : maybe TSK should know this
		Link->PlayMontage(LINK_MONTAGE::ITEM_GET);
		Link->SetOffAnimStatus(LINK_BIT_CARRY);
		OnLinkItemGet.Broadcast(Link->GetActorLocation(), Link->GetActorForwardVector());
		UKismetSystemLibrary::K2_SetTimer(this, TEXT("CallOnLinkItemGetEnd"), 1.f, false);
	}
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

void ALinkController::CallOnLinkItemGetEnd()
{
	OnLinkItemGetEnd.Broadcast();
	ALink* Link = Cast<ALink>(GetPawn());
	Link->DestoryCatchingItem();
}

