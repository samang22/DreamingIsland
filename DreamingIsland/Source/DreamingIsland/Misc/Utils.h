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

namespace Monster_SocketName
{
	static inline FName Weapon = TEXT("Weapon");
}

namespace CollisionProfileName
{
	static inline FName Link = TEXT("Link");
	static inline FName Monster = TEXT("Monster");
	static inline FName LinkProjectile = TEXT("LinkProjectile");
	static inline FName MonsterProjectile = TEXT("MonsterProjectile");
	static inline FName MonsterBodyProjectile = TEXT("MonsterBodyProjectile");
	static inline FName BombProjectile = TEXT("BombProjectile");
	static inline FName MapMesh = TEXT("MapMesh");
}

namespace ProjectileName
{
	static inline FName Link_SlashAttack = TEXT("Link_SlashAttack");
	static inline FName Albatoss_ClawAttack = TEXT("Albatoss_ClawAttack");
	static inline FName Octorok_RockAttack = TEXT("Octorok_RockAttack");
	static inline FName Moblin_SpearAttack = TEXT("Moblin_SpearAttack");
	static inline FName Hinox_Bomb = TEXT("Hinox_Bomb");
	static inline FName Hinox_Catch = TEXT("Hinox_Catch");
	static inline FName Hinox_Link = TEXT("Hinox_Link");
	static inline FName Bomber_Bomb = TEXT("Bomber_Bomb");
}

#define COLLISION_CHANNEL_LINKCHANNEL						ECC_GameTraceChannel1
#define COLLISION_CHANNEL_MONSTERCHANNEL					ECC_GameTraceChannel2
#define COLLISION_CHANNEL_LINKPROJECTILECHANNEL				ECC_GameTraceChannel3
#define COLLISION_CHANNEL_MONSTERPROJECTILECHANNEL			ECC_GameTraceChannel4
#define COLLISION_CHANNEL_LINK								ECC_GameTraceChannel5
#define COLLISION_CHANNEL_MONSTER							ECC_GameTraceChannel6
#define COLLISION_CHANNEL_LINKPROJECTILE					ECC_GameTraceChannel7
#define COLLISION_CHANNEL_MONSTERPROJECTILE					ECC_GameTraceChannel8
#define COLLISION_CHANNEL_MONSTERBODYPROJECTILE				ECC_GameTraceChannel9
#define COLLISION_CHANNEL_BOMBPROJECTILE					ECC_GameTraceChannel10
#define COLLISION_CHANNEL_BOMBPROJECTILECHANNEL				ECC_GameTraceChannel11


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

