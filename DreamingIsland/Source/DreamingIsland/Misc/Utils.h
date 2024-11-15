// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once
#include "CoreMinimal.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"


#define COLLISION_HIDDEN_IN_GAME						false
#define CRANEGAME_COST									10
#define MAGNET_FORCE									200000.f

#define CUCCO_MAX_NUM									8

#define PROBE_SIZE										5.0
#define COLLISION_SPHERE_RADIUS							24.f
#define LINK_WALK_SPEED									500.f
#define LINK_RUN_SPEED									1000.f
#define LINK_SENSEINTERACTIVE_COLLISION_SPHERE_RADIUS	48.f
#define LINK_SENSE_COLLISION_OFFSET						48.f
#define LINK_CAPSULE_HALF_HEIGHT						200.f

#define LINK_SPOTLIGHT_ANGLE							45.f
#define LINK_SPOTLIGHT_INTENSITY						100000.f


#define LINK_ITEM_GET_FORWARD_OFFSET 150.f
#define LINK_ITEM_GET_UP_OFFSET 150.f

#define FISHINGLINK_FISH_GET_UP_OFFSET 50.f

#define FISHINGPOND_ACTOR_Y								105.f

#define FISH_AISENSECONFIG_SIGHT_SIGHTRADIUS										200.f
#define FISH_AISENSECONFIG_SIGHT_LOSESIGHTRADIUS									220.f
#define FISH_AISENSECONFIG_SIGHT_PERIPHERALVISIONANGLEDEGREES						180.f

#define SMALLFISH_MOVE_FORCE			2000.f
#define BIGFISH_MOVE_FORCE				2000.f

#define SMALLFISH_PULL_FORCE 1000.f
#define BIGFISH_PULL_FORCE 1400.f

#define FISH_POKE_DISTANCE 100.f

#define LURE_VELOCITY_LIMIT 150.f

#define LURE_PULL_FORCE 360000.f
#define FISHINGLINK_PULL_FORCE 150000.f

#define LURE_BACK_TO_LINK_DISTANCE 250.f




enum class FISHINGLINK_STATUS : uint8
{
	IDLE = 0,
	FISHING,
	PULLING,
	END,
};

enum class FISH_STATUS : uint8
{
	IDLE = 0,
	POKE,
	FIGHTING,
	CATCHED,
	END,
};

enum class FISHINGROD_STATUS : uint8
{
	IDLE = 0,
	FIGHTING,
	FISH_LOST,
	THROW_ST,
	THROW_ED,
	END,
};

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
	static inline FName BlockAllDynamic = TEXT("BlockAllDynamic");
	static inline FName BlockAll = TEXT("BlockAll");
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
	static inline FName Magnet = TEXT("Magnet");
	static inline FName Lure = TEXT("Lure");
	static inline FName Fish = TEXT("Fish");
	static inline FName FishingLink = TEXT("FishingLink");
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
	static inline FName Link_Throw = TEXT("Link_Throw");
	static inline FName Link_Lure = TEXT("Link_Lure");
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

namespace GSO_ConversationKey
{
	static inline FString Greeting = TEXT("Greeting");
	static inline FString Try = TEXT("Try");
	static inline FString End = TEXT("End");
	static inline FString Rage = TEXT("Rage");
	static inline FString BuySucceeded = TEXT("BuySuceeded");
	static inline FString BuyFailed = TEXT("BuyFailed");
}

namespace CK_ConversationKey
{
	static inline FString Greeting = TEXT("Greeting");
	static inline FString Request = TEXT("Request");
	static inline FString Accept = TEXT("Accept");
	static inline FString Thanks = TEXT("Thanks");
	static inline FString Bad = TEXT("Bad");
	static inline FString NotYet = TEXT("NotYet");
}

namespace FM_ConversationKey
{
	static inline FString Greeting = TEXT("Greeting");
	static inline FString Try = TEXT("Try");
	static inline FString Accept = TEXT("Accept");
	static inline FString Bad = TEXT("Bad");
}

namespace NPC_Name_Korean
{
	static inline FName ToolShopKeeper = TEXT("도구 상점 주인");
	static inline FName GameShopOwner = TEXT("게임샵 주인");
	static inline FName CraneButton = TEXT("크레인 버튼");
	static inline FName CuccoKeeper = TEXT("닭장 주인");
	static inline FName Cucco = TEXT("닭");
	static inline FName FisherMan = TEXT("낚시꾼");
	static inline FName Fish = TEXT("물고기");
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

enum class FISHINGLINK_MONTAGE : uint8
{
	THROW_LURE = 0,
	FISH_LOST,
	FISH_GET,
	FISH_HANG,
	END,
};

enum class FISH_MONTAGE : uint8
{
	POKE = 0,
	TURN,
	END,
};

enum class LINK_MATERIAL : uint8
{
	MAGICROD = 0,
	OCARINA,
	SHOVEL,
	BODY,
	BOOTS,
	EAR,
	EYE,
	MOUTH,
	FLIPPERS,
	HAIR,
	HOOKSHOT,
	SHIELDA,
	SHIELDB,
	SHIELDB_MIRROR,
	SWORDA,
	SWORDA_BALL,
	SWORDB,
	SWORDB_BALL,
	END
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


#define	LINK_BIT_WAIT			0x00000001
#define	LINK_BIT_WALK			0x00000002
#define	LINK_BIT_RUN			0x00000004
#define	LINK_BIT_CARRY			0x00000008

#define FISHINGLINK_BIT_IDLE		0x00000001
#define FISHINGLINK_BIT_FISHING		0x00000002
#define FISHINGLINK_BIT_PULLING		0x00000004


#define LINK_TOOL_BIT_SWORD				0x00000001
#define LINK_TOOL_BIT_SHIELD			0x00000002
#define LINK_TOOL_BIT_MIRRORSHIELD		0x00000004
#define LINK_TOOL_BIT_FLIPPER			0x00000008
#define LINK_TOOL_BIT_OCARINA			0x00000010
#define LINK_TOOL_BIT_BOW				0x00000011

#define LINK_LOCATION_OFFSET 70.f

#define MONSTER_BIT_WAIT			0x00000001
#define MONSTER_BIT_WALK			0x00000002
#define MONSTER_BIT_RUN				0x00000004
#define MONSTER_BIT_RUSH			0x00000008
#define MONSTER_BIT_HOLDING_WEAPON	0x00000010

#define NPC_BIT_WAIT			0x00000001
#define NPC_BIT_WALK			0x00000002
#define NPC_BIT_TALK			0x00000004
#define NPC_BIT_RUN				0x00000008
#define NPC_BIT_LIFTED			0x00000010
#define NPC_BIT_THROWN			0x00000020

#define FISH_BIT_WAIT			0x00000001
#define FISH_BIT_POKEWAIT		0x00000002
#define FISH_BIT_GET			0x00000004
#define FISH_BIT_CATCHING		0x00000008


#define FISHINGROD_BIT_IDLE			0x00000001
#define FISHINGROD_BIT_FIGHTING		0x00000002
#define FISHINGROD_BIT_FISHLOST		0x00000004
#define FISHINGROD_BIT_THROW_ST		0x00000008
#define FISHINGROD_BIT_THROW_ED		0x00000010



#define CUCCO_AISENSECONFIG_SIGHT_SIGHTRADIUS										300.f
#define CUCCO_AISENSECONFIG_SIGHT_LOSESIGHTRADIUS									600.f
#define CUCCO_AISENSECONFIG_SIGHT_LOSESIGHTRADIUS_PERIPHERALVISIONANGLEDEGREES		360.f

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