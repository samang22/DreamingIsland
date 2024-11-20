// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Link/LinkController.h"
#include "LinkController.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/Character.h"
#include "Components/SoftWheelSpringArmComponent.h"
#include "Components/StatusComponent/LinkStatusComponent.h"
#include "Actors/Link/LinkCameraManager.h"
#include "Actors/Link/Link.h"
#include "Actors/NPC/NPC.h"
#include "Actors/NPC/ToolShopKeeper.h"
#include "Actors/NPC/GameShopOwner.h"
#include "Actors/NPC/Cucco.h"
#include "Actors/NPC/Crane.h"
#include "Actors/Items/Item.h"
#include "Actors/Default/DefaultHUD.h"
#include "Animation/LinkAnimInstance.h"
#include "Kismet/GameplayStatics.h"
#include "GameInstance/DreamingIsland_GIS.h"
#include "GameInstance/Conversation_GIS.h"

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
		EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Started, this, &ThisClass::OnAttack);
		EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Completed, this, &ThisClass::OnCheck);
		EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Completed, this, &ThisClass::OnCraneDown);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("IA_Attack is disabled"));
	}

	if (const UInputAction* InputAction = FUtils::GetInputActionFromName(IMC_Default, TEXT("IA_Interact")))
	{
		EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Completed, this, &ThisClass::OnInteract);
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

	if (const UInputAction* InputAction = FUtils::GetInputActionFromName(IMC_Default, TEXT("IA_Throw")))
	{
		EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Completed, this, &ThisClass::OnThrow);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("IA_Throw is disabled"));
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
		DefaultHUD->OnSetArrowNum(StatusComponent->GetArrow());
		DefaultHUD->OnSetBombNum(StatusComponent->GetBomb());
	}
}

void ALinkController::OnWalk(const FInputActionValue& InputActionValue)
{
	if (StatusComponent->GetIsConversation()) return;

	ALink* Link = Cast<ALink>(GetPawn());
	if (Link->IsPlayingMontage(LINK_MONTAGE::SLASH)) return;


	const FVector ForwardVector = FVector(1.0, 0.0, 0.0);
	const FVector RightVector = FVector(0.0, 1.0, 0.0);
	const FVector2D ActionValue = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = K2_GetActorRotation();
	const FRotator RotationYaw = FRotator(0.0, Rotation.Yaw, 0.0);

	ACrane* Crane = StatusComponent->GetCrane();
	if (Crane)
	{
		Crane->Move(ForwardVector, ActionValue.X);
		Crane->Move(RightVector, ActionValue.Y);
		return;
	}


	StatusComponent->SetOnAnimationStatus(LINK_BIT_WALK);


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
	if (StatusComponent->GetIsConversation() || StatusComponent->GetCrane()) return;
	ALink* Link = Cast<ALink>(GetPawn());
	if (!StatusComponent->GetToolEquipStatus(LINK_TOOL_BIT_SWORD)) return;
	Link->PlayMontage(LINK_MONTAGE::SLASH);
}

void ALinkController::OnInteract(const FInputActionValue& InputActionValue)
{
	if (StatusComponent->GetCrane()) return;

	ALink* Link = Cast<ALink>(GetPawn());
	if (Link->IsOverlappedNPC())
	{
		ANPC* NPC = Cast<ANPC>(Link->GetOverlappedNPC());

		if (ACucco* Cucco = Cast<ACucco>(NPC))
		{
			Link->CatchCucco();
		}
		else
		{
			UConversation_GIS* Conversation_GIS = GetGameInstance()->GetSubsystem<UConversation_GIS>();
			bool bCheckBroadcast = false;
			Conversation_GIS->Conversation(Link, NPC, bCheckBroadcast);
			if (bCheckBroadcast)
			{
				//Link->DeActiveSpringArm();
				OnLinkTalk.Broadcast(Link->GetActorLocation(), -1 * Link->GetActorRightVector(), Link->GetActorForwardVector());
			}
		}
	}
	else if (Link->IsOverlappedItem()
		&& !Link->IsCatchingActor()
		)
	{
		AnimInstance->PlayMontage(LINK_MONTAGE::ITEM_CARRY);
		Link->CatchItem();
	}
	 
}

void ALinkController::OnLay(const FInputActionValue& InputActionValue)
{
	if (StatusComponent->GetCrane()) return;

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

	if (Link->IsCatchingActor()
	&& !Link->IsPlayingMontage(LINK_MONTAGE::END))
	{
		Link->ActorThrown();
	}


	


}

void ALinkController::OnZoomWheel(const FInputActionValue& InputActionValue)
{
}

// Change Selection
void ALinkController::OnChoose(const FInputActionValue& InputActionValue)
{
	if (!StatusComponent->GetIsConversation()) return;

	const FVector2D ActionValue = InputActionValue.Get<FVector2D>();
	ADefaultHUD* DefaultHUD = Cast<ADefaultHUD>(GetHUD());
	DefaultHUD->OnSetSelection(ActionValue.Y < 0 ? true : false);
}

// Decide Selection
void ALinkController::OnCheck(const FInputActionValue& InputActionValue)
{
	if (!StatusComponent->GetIsConversation() || StatusComponent->GetCrane()) return;

	ADefaultHUD* DefaultHUD = Cast<ADefaultHUD>(GetHUD());
	if (!DefaultHUD->GetIsChooseWidgetVisible()) return;

	ALink* Link = Cast<ALink>(GetPawn());
	AActor* OverlappedNPC = Link->GetOverlappedNPC();
	ANPC* NPC = Cast<ANPC>(OverlappedNPC);

	UConversation_GIS* Conversation_GIS = GetGameInstance()->GetSubsystem<UConversation_GIS>();
	bool bCheckEndTalk = false;
	Conversation_GIS->Check(Link, NPC, bCheckEndTalk, DefaultHUD->GetSelection());

	if (bCheckEndTalk)
	{
		DefaultHUD->OnHideChooseWidget();
		DefaultHUD->OnHideConversationWidget();
		DefaultHUD->OnHideRupeeWidget();
		OnLinkTalkEnd.Broadcast();
	}



	//if (DefaultHUD->GetSelection())
	//{
	//	// now check which one is talking with
	//	ALink* Link = Cast<ALink>(GetPawn());
	//	AActor* OverlappedNPC = Link->GetOverlappedNPC();
	//	ANPC* NPC = Cast<ANPC>(OverlappedNPC);
	//	UConversation_GIS* Conversation_GIS = GetGameInstance()->GetSubsystem<UConversation_GIS>();
	//	bool bCheckBroadcast = false;
	//	Conversation_GIS->Purchase(Link, NPC, bCheckBroadcast);
	//	StatusComponent->SetIsConversation(false);
	//}
	//else
	//{
	//	OnLinkTalkEnd.Broadcast();
	//	StatusComponent->SetIsConversation(false);
	//	DefaultHUD->OnHideChooseWidget();
	//	DefaultHUD->OnHideConversationWidget();
	//	DefaultHUD->OnHideRupeeWidget();
	//}

}

void ALinkController::OnGet(const FInputActionValue& InputActionValue)
{
	ALink* Link = Cast<ALink>(GetPawn());
	if (Link->IsCatchingActor())
	{
		AItem* Item = Cast<AItem>(Link->GetCatchingActor());
		Link->SetIsThief(!Item->GetIsPurchased());
		FName ItemName = Item->GetItemName();

		if (Item_Name::Bomb == ItemName)
		{
			StatusComponent->AddBomb(5);
			ADefaultHUD* DefaultHUD = Cast<ADefaultHUD>(GetHUD());
			DefaultHUD->OnSetBombNum(StatusComponent->GetBomb());
		}
		else if (Item_Name::Arrow == ItemName)
		{
			StatusComponent->AddArrow(5);
			ADefaultHUD* DefaultHUD = Cast<ADefaultHUD>(GetHUD());
			DefaultHUD->OnSetArrowNum(StatusComponent->GetArrow());
		}
		else if (Item_Name::Bow == ItemName)
		{
			StatusComponent->SetOnToolEquipStatus(LINK_TOOL_BIT_BOW);
		}
		else if (Item_Name::Shield == ItemName)
		{
			StatusComponent->SetOnToolEquipStatus(LINK_TOOL_BIT_SHIELD);
			Link->SetMaterialOpacity(LINK_MATERIAL::SHIELDA, 1.f);
		}
		else if (Item_Name::Sword == ItemName)
		{
			StatusComponent->SetOnToolEquipStatus(LINK_TOOL_BIT_SWORD);
			Link->SetMaterialOpacity(LINK_MATERIAL::SWORDA, 1.f);
			Link->SetMaterialOpacity(LINK_MATERIAL::SWORDA_BALL, 1.f);
		}
		else if (Item_Name::RupeeGreen == ItemName
			|| Item_Name::RupeeBlue == ItemName
			|| Item_Name::RupeeGold == ItemName)
		{
			StatusComponent->AddRupee(Item->GetItemValue());
			ADefaultHUD* DefaultHUD = Cast<ADefaultHUD>(GetHUD());
			DefaultHUD->OnSetArrowNum(StatusComponent->GetRupee());
		}

		Link->PlayMontage(LINK_MONTAGE::ITEM_GET);
		Link->SetOffAnimStatus(LINK_BIT_CARRY);
		OnLinkItemGet.Broadcast(Link->GetActorLocation(), Link->GetActorForwardVector());
		UKismetSystemLibrary::K2_SetTimer(this, TEXT("CallOnLinkItemGetEnd"), 1.f, false);
	}
}

void ALinkController::OnCraneDown(const FInputActionValue& InputActionValue)
{
	if (!StatusComponent->GetCrane()) return;
	ACrane* Crane = StatusComponent->GetCrane();
	if (!Crane->GetIsStart()) return;
	Crane->Down();
	StatusComponent->ClearCrane();
}

void ALinkController::OnThrow(const FInputActionValue& InputActionValue)
{
	if (StatusComponent->GetIsConversation() || StatusComponent->GetCrane()) return;
	ALink* Link = Cast<ALink>(GetPawn());
	if (Link->IsCatchingActor())
	{
		Cast<ALink>(GetPawn())->PlayMontage(LINK_MONTAGE::THROW);
	}
}

void ALinkController::OnBomb(const FInputActionValue& InputActionValue)
{
	if (StatusComponent->GetIsConversation() || StatusComponent->GetCrane()) return;

	if (StatusComponent->GetBomb() <= 0) return;
	
	ALink* Link = Cast<ALink>(GetPawn());
	//Link->SetCatchingItem();
	AnimInstance->PlayMontage(LINK_MONTAGE::ITEM_CARRY);
	Link->CatchItem();
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

