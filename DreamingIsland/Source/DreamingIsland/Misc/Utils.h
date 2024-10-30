// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once
#include "CoreMinimal.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"


#define COLLISION_HIDDEN_IN_GAME						false


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
	static inline FName ItemCarry = TEXT("ItemCarry");
}

namespace Monster_SocketName
{
	static inline FName Weapon = TEXT("Weapon");
}

namespace NPC_SocketName
{
	static inline FName Light = TEXT("Light");
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
	static inline FName SenseLink = TEXT("SenseLink");
	static inline FName NPC = TEXT("NPC");
	static inline FName Item = TEXT("Item");
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




#define TRACE_CHANNEL_LINKCHANNEL						ECC_GameTraceChannel1
#define TRACE_CHANNEL_MONSTERCHANNEL					ECC_GameTraceChannel2
#define TRACE_CHANNEL_ITEM								ECC_GameTraceChannel3
#define TRACE_CHANNEL_LINK								ECC_GameTraceChannel5
#define TRACE_CHANNEL_MONSTER							ECC_GameTraceChannel6
#define TRACE_CHANNEL_LINKPROJECTILE					ECC_GameTraceChannel7
#define TRACE_CHANNEL_MONSTERPROJECTILE					ECC_GameTraceChannel8
#define TRACE_CHANNEL_MONSTERBODYPROJECTILE				ECC_GameTraceChannel9
#define TRACE_CHANNEL_BOMBPROJECTILE					ECC_GameTraceChannel10
#define TRACE_CHANNEL_DECORATIONMAPMESH					ECC_GameTraceChannel12
#define TRACE_CHANNEL_MAPMESH							ECC_GameTraceChannel13
#define TRACE_CHANNEL_SENSELINK							ECC_GameTraceChannel14
#define TRACE_CHANNEL_NPC								ECC_GameTraceChannel15
#define TRACE_CHANNEL_INVISIBLECOLLIDER					ECC_GameTraceChannel16
#define TRACE_CHANNEL_SENSEINTERACTIVE					ECC_GameTraceChannel18


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

inline bool IsNearlyEqualVector_My(const FVector& A, const FVector& B, float Tolerance = KINDA_SMALL_NUMBER)
{
	return FVector::DistSquared(A, B) < FMath::Square(Tolerance);
}
