// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once
#include "CoreMinimal.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

class FUtils
{
public:
	static const UInputAction* GetInputActionFromName(UInputMappingContext* IMC, const FName& InName)
	{
		const TArray<FEnhancedActionKeyMapping>& Mappings = IMC->GetMappings();
		for (auto& It : Mappings)
		{
			if (It.Action->GetFName() == InName)
			{
				return It.Action.Get();
			}
		}

		return nullptr;
	}
};

namespace Link_SocketName
{
	static inline FName SwordTop = TEXT("itemA_L_top");
}

namespace Link_SocketName_FString
{
	static inline FString SwordTop = TEXT("itemA_L_top");
}

namespace Monster_SocketName
{
	static inline FName Weapon = TEXT("Weapon");
}

namespace Monster_SocketName_FString
{
	static inline FString Weapon = TEXT("Weapon");
}
namespace CollisionProfileName
{
	static inline FName Link = TEXT("Link");
	static inline FName Monster = TEXT("Monster");
	static inline FName Link_Projectile = TEXT("LinkProjectile");
	static inline FName Monster_Projectile = TEXT("MonsterProjectile");
}

namespace ProjectileName
{
	static inline FName Link_SlashAttack = TEXT("Link_SlashAttack");
	static inline FName Albatoss_ClawAttack = TEXT("Albatoss_ClawAttack");
	static inline FName Octorok_RockAttack = TEXT("Octorok_RockAttack");
	static inline FName Moblin_SpearAttack = TEXT("Moblin_SpearAttack");
}

#define COLLISION_CHANNEL_LINKCHANNEL				ECollisionChannel::ECC_GameTraceChannel1
#define COLLISION_CHANNEL_MONSTERCHANNEL			ECollisionChannel::ECC_GameTraceChannel2
#define COLLISION_CHANNEL_LINKPROJECTILECHANNEL		ECollisionChannel::ECC_GameTraceChannel3
#define COLLISION_CHANNEL_MONSTERPROJECTILECHANNEL	ECollisionChannel::ECC_GameTraceChannel4
#define COLLISION_CHANNEL_LINK						ECollisionChannel::ECC_GameTraceChannel5
#define COLLISION_CHANNEL_MONSTER					ECollisionChannel::ECC_GameTraceChannel6
#define COLLISION_CHANNEL_LINKPROJECTILE			ECollisionChannel::ECC_GameTraceChannel7
#define COLLISION_CHANNEL_MONSTERPROJECTILE			ECollisionChannel::ECC_GameTraceChannel8


namespace MonsterName
{
	static inline FName Albatoss = TEXT("Albatoss");
	static inline FName Octorok = TEXT("Octorok");
}

namespace MonsterName_FString
{
	static inline FString Albatoss = TEXT("Albatoss");
	static inline FString Octorok = TEXT("Octorok");
}

