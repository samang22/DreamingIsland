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
	static inline FName SenseInteractive = TEXT("SenseInteractive");
	static inline FName MyTrigger = TEXT("MyTrigger");
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

namespace TSK_ConversationKey
{
	static inline FString Greeting = TEXT("Greeting");
	static inline FString Blame = TEXT("Blame");
	static inline FString Bye = TEXT("Bye");
	static inline FString Buy1 = TEXT("Buy1");
	static inline FString Buy2 = TEXT("Buy2");
	static inline FString BuySucceeded = TEXT("BuySuceeded");
	static inline FString BuyFailed = TEXT("BuyFailed");
	static inline FString Mad = TEXT("Mad");
}

namespace NPC_Name_Korean
{
	static inline FName ToolShopKeeper = TEXT("도구 상점 주인");
}


namespace Item_Name
{
	static inline FName Bomb = TEXT("Bomb");
	static inline FName Arrow = TEXT("Arrow");
	static inline FName Bow = TEXT("Bow");
	static inline FName Shield = TEXT("Shield");
	static inline FName Sword = TEXT("Sword");
	static inline FName RupeeGreen = TEXT("RupeeGreen");
	static inline FName RupeeBlue = TEXT("RupeeBlue");
	static inline FName RupeeGold = TEXT("RupeeGold");
}

enum class LINK_MONTAGE : uint8
{
	SLASH = 0,
	ITEM_CARRY,
	ITEM_GET,
	DEAD,
	DAMAGE,
	THROW,
	GUARD,
	END,
};


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

inline float CalculateAngleBetweenVectors(const FVector& A, const FVector& B) 
{
	// Calculate dot product
	float DotProduct = FVector::DotProduct(A, B);

	// 두 벡터의 크기를 계산
	float MagnitudeA = A.Size();
	float MagnitudeB = B.Size();

	// 코사인 값 계산
	float CosTheta = DotProduct / (MagnitudeA * MagnitudeB);

	// 각도 계산 (라디안)
	float AngleRadians = FMath::Acos(CosTheta);

	// 라디안을 각도로 변환
	return FMath::RadiansToDegrees(AngleRadians);
}