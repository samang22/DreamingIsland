// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DreamingIsland/Animation/AlbatossAnimInstance.h"
#include "Runtime/Engine/Classes/Components/SkeletalMeshComponent.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeAlbatossAnimInstance() {}

// Begin Cross Module References
DREAMINGISLAND_API UClass* Z_Construct_UClass_UAlbatossAnimInstance();
DREAMINGISLAND_API UClass* Z_Construct_UClass_UAlbatossAnimInstance_NoRegister();
DREAMINGISLAND_API UClass* Z_Construct_UClass_UMonsterAnimInstance();
UPackage* Z_Construct_UPackage__Script_DreamingIsland();
// End Cross Module References

// Begin Class UAlbatossAnimInstance
void UAlbatossAnimInstance::StaticRegisterNativesUAlbatossAnimInstance()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UAlbatossAnimInstance);
UClass* Z_Construct_UClass_UAlbatossAnimInstance_NoRegister()
{
	return UAlbatossAnimInstance::StaticClass();
}
struct Z_Construct_UClass_UAlbatossAnimInstance_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "HideCategories", "AnimInstance" },
		{ "IncludePath", "Animation/AlbatossAnimInstance.h" },
		{ "ModuleRelativePath", "Animation/AlbatossAnimInstance.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bIsDead_MetaData[] = {
		{ "Category", "AlbatossAnimInstance" },
		{ "ModuleRelativePath", "Animation/AlbatossAnimInstance.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bIsDamage_MetaData[] = {
		{ "Category", "AlbatossAnimInstance" },
		{ "ModuleRelativePath", "Animation/AlbatossAnimInstance.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bIsAttack_MetaData[] = {
		{ "Category", "AlbatossAnimInstance" },
		{ "ModuleRelativePath", "Animation/AlbatossAnimInstance.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bIsRush_MetaData[] = {
		{ "Category", "AlbatossAnimInstance" },
		{ "ModuleRelativePath", "Animation/AlbatossAnimInstance.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bIsWait_MetaData[] = {
		{ "Category", "AlbatossAnimInstance" },
		{ "ModuleRelativePath", "Animation/AlbatossAnimInstance.h" },
	};
#endif // WITH_METADATA
	static void NewProp_bIsDead_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bIsDead;
	static void NewProp_bIsDamage_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bIsDamage;
	static void NewProp_bIsAttack_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bIsAttack;
	static void NewProp_bIsRush_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bIsRush;
	static void NewProp_bIsWait_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bIsWait;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UAlbatossAnimInstance>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
void Z_Construct_UClass_UAlbatossAnimInstance_Statics::NewProp_bIsDead_SetBit(void* Obj)
{
	((UAlbatossAnimInstance*)Obj)->bIsDead = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UAlbatossAnimInstance_Statics::NewProp_bIsDead = { "bIsDead", nullptr, (EPropertyFlags)0x0020080000000014, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UAlbatossAnimInstance), &Z_Construct_UClass_UAlbatossAnimInstance_Statics::NewProp_bIsDead_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bIsDead_MetaData), NewProp_bIsDead_MetaData) };
void Z_Construct_UClass_UAlbatossAnimInstance_Statics::NewProp_bIsDamage_SetBit(void* Obj)
{
	((UAlbatossAnimInstance*)Obj)->bIsDamage = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UAlbatossAnimInstance_Statics::NewProp_bIsDamage = { "bIsDamage", nullptr, (EPropertyFlags)0x0020080000000014, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UAlbatossAnimInstance), &Z_Construct_UClass_UAlbatossAnimInstance_Statics::NewProp_bIsDamage_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bIsDamage_MetaData), NewProp_bIsDamage_MetaData) };
void Z_Construct_UClass_UAlbatossAnimInstance_Statics::NewProp_bIsAttack_SetBit(void* Obj)
{
	((UAlbatossAnimInstance*)Obj)->bIsAttack = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UAlbatossAnimInstance_Statics::NewProp_bIsAttack = { "bIsAttack", nullptr, (EPropertyFlags)0x0020080000000014, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UAlbatossAnimInstance), &Z_Construct_UClass_UAlbatossAnimInstance_Statics::NewProp_bIsAttack_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bIsAttack_MetaData), NewProp_bIsAttack_MetaData) };
void Z_Construct_UClass_UAlbatossAnimInstance_Statics::NewProp_bIsRush_SetBit(void* Obj)
{
	((UAlbatossAnimInstance*)Obj)->bIsRush = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UAlbatossAnimInstance_Statics::NewProp_bIsRush = { "bIsRush", nullptr, (EPropertyFlags)0x0020080000000014, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UAlbatossAnimInstance), &Z_Construct_UClass_UAlbatossAnimInstance_Statics::NewProp_bIsRush_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bIsRush_MetaData), NewProp_bIsRush_MetaData) };
void Z_Construct_UClass_UAlbatossAnimInstance_Statics::NewProp_bIsWait_SetBit(void* Obj)
{
	((UAlbatossAnimInstance*)Obj)->bIsWait = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UAlbatossAnimInstance_Statics::NewProp_bIsWait = { "bIsWait", nullptr, (EPropertyFlags)0x0020080000000014, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UAlbatossAnimInstance), &Z_Construct_UClass_UAlbatossAnimInstance_Statics::NewProp_bIsWait_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bIsWait_MetaData), NewProp_bIsWait_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UAlbatossAnimInstance_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAlbatossAnimInstance_Statics::NewProp_bIsDead,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAlbatossAnimInstance_Statics::NewProp_bIsDamage,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAlbatossAnimInstance_Statics::NewProp_bIsAttack,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAlbatossAnimInstance_Statics::NewProp_bIsRush,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAlbatossAnimInstance_Statics::NewProp_bIsWait,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UAlbatossAnimInstance_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UAlbatossAnimInstance_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UMonsterAnimInstance,
	(UObject* (*)())Z_Construct_UPackage__Script_DreamingIsland,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UAlbatossAnimInstance_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UAlbatossAnimInstance_Statics::ClassParams = {
	&UAlbatossAnimInstance::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_UAlbatossAnimInstance_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_UAlbatossAnimInstance_Statics::PropPointers),
	0,
	0x009000A8u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UAlbatossAnimInstance_Statics::Class_MetaDataParams), Z_Construct_UClass_UAlbatossAnimInstance_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UAlbatossAnimInstance()
{
	if (!Z_Registration_Info_UClass_UAlbatossAnimInstance.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UAlbatossAnimInstance.OuterSingleton, Z_Construct_UClass_UAlbatossAnimInstance_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UAlbatossAnimInstance.OuterSingleton;
}
template<> DREAMINGISLAND_API UClass* StaticClass<UAlbatossAnimInstance>()
{
	return UAlbatossAnimInstance::StaticClass();
}
UAlbatossAnimInstance::UAlbatossAnimInstance(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UAlbatossAnimInstance);
UAlbatossAnimInstance::~UAlbatossAnimInstance() {}
// End Class UAlbatossAnimInstance

// Begin Registration
struct Z_CompiledInDeferFile_FID_Minhyeok_DreamingIsland_DreamingIsland_Source_DreamingIsland_Animation_AlbatossAnimInstance_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UAlbatossAnimInstance, UAlbatossAnimInstance::StaticClass, TEXT("UAlbatossAnimInstance"), &Z_Registration_Info_UClass_UAlbatossAnimInstance, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UAlbatossAnimInstance), 1788161552U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Minhyeok_DreamingIsland_DreamingIsland_Source_DreamingIsland_Animation_AlbatossAnimInstance_h_1981540373(TEXT("/Script/DreamingIsland"),
	Z_CompiledInDeferFile_FID_Minhyeok_DreamingIsland_DreamingIsland_Source_DreamingIsland_Animation_AlbatossAnimInstance_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Minhyeok_DreamingIsland_DreamingIsland_Source_DreamingIsland_Animation_AlbatossAnimInstance_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
