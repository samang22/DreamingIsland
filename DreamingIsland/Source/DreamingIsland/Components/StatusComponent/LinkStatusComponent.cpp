// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/StatusComponent/LinkStatusComponent.h"
#include "Misc/Utils.h"
#include "Actors/Default/DefaultHUD.h"
#include "Actors/Link/LinkController.h"

ULinkStatusComponent::ULinkStatusComponent()
{
	SetOnAnimationStatus(LINK_BIT_WAIT);
	AddRupee(100);
}

void ULinkStatusComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void ULinkStatusComponent::SetOnAnimationStatus(uint8 InBit)
{
	LinkAnimationStatus |= InBit;
}

void ULinkStatusComponent::SetOffAnimationStatus(uint8 InBit)
{
	LinkAnimationStatus &= ~(InBit);
}

//void ULinkStatusComponent::SetOnToolOwnStatus(uint8 InBit)
//{
//	LinkToolOwnStatus |= InBit;
//}
//
//void ULinkStatusComponent::SetOffToolOwnStatus(uint8 InBit)
//{
//	LinkToolOwnStatus &= ~(InBit);
//}

void ULinkStatusComponent::SetOnToolEquipStatus(uint8 InBit)
{
	LinkToolEquipStatus |= InBit;
}

void ULinkStatusComponent::SetOffToolEquipStatus(uint8 InBit)
{
	LinkToolEquipStatus &= ~(InBit);
}

bool ULinkStatusComponent::GetAnimStatus(uint8 InBit) const
{
	return LinkAnimationStatus & InBit;
}

//bool ULinkStatusComponent::GetToolOwnStatus(uint8 InBit) const
//{
//	return LinkToolOwnStatus & InBit;
//}
bool ULinkStatusComponent::GetToolEquipStatus(uint8 InBit) const
{
	return LinkToolEquipStatus & InBit;
}
uint8 ULinkStatusComponent::GetEntireToolEquipStatus() const
{
	return LinkToolEquipStatus;
}

void ULinkStatusComponent::SetRupee(int _Rupee)
{
	Rupee = _Rupee;

	if (GetWorld() && GetWorld()->IsGameWorld())
	{
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		ADefaultHUD* DefaultHUD = Cast<ADefaultHUD>(PlayerController->GetHUD());
		if (DefaultHUD)
		{
			DefaultHUD->OnShowRupeeWidget();
		}
	}
}

void ULinkStatusComponent::AddRupee(int _Rupee)
{
	Rupee += _Rupee;

	if (GetWorld() && GetWorld()->IsGameWorld())
	{

		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		ADefaultHUD* DefaultHUD = Cast<ADefaultHUD>(PlayerController->GetHUD());
		if (DefaultHUD)
		{
			DefaultHUD->OnShowRupeeWidget();
		}
	}
}

int ULinkStatusComponent::GetRupee() const
{
	return Rupee;
}

void ULinkStatusComponent::SetBomb(int _Bomb)
{
	Bomb = _Bomb;

	if (GetWorld() && GetWorld()->IsGameWorld())
	{

		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		ADefaultHUD* DefaultHUD = Cast<ADefaultHUD>(PlayerController->GetHUD());
		if (DefaultHUD)
		{
			DefaultHUD->OnShowBombWidget();
		}
	}
}

void ULinkStatusComponent::AddBomb(int _Bomb)
{
	Bomb += _Bomb;

	if (GetWorld() && GetWorld()->IsGameWorld())
	{

		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		ADefaultHUD* DefaultHUD = Cast<ADefaultHUD>(PlayerController->GetHUD());
		if (DefaultHUD)
		{
			DefaultHUD->OnShowBombWidget();
		}
	}
}

int ULinkStatusComponent::GetBomb() const
{
	return Bomb;
}

void ULinkStatusComponent::SetArrow(int _Arrow)
{
	Arrow = _Arrow;
	
	if (GetWorld() && GetWorld()->IsGameWorld())
	{

		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		ADefaultHUD* DefaultHUD = Cast<ADefaultHUD>(PlayerController->GetHUD());
		if (DefaultHUD)
		{
			DefaultHUD->OnShowArrowWidget();
		}
	}
}

void ULinkStatusComponent::AddArrow(int _Arrow)
{
	Arrow += _Arrow;

	if (GetWorld() && GetWorld()->IsGameWorld())
	{

		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		ADefaultHUD* DefaultHUD = Cast<ADefaultHUD>(PlayerController->GetHUD());
		if (DefaultHUD)
		{
			DefaultHUD->OnShowArrowWidget();
		}
	}
}

int ULinkStatusComponent::GetArrow() const
{
	return Arrow;
}
