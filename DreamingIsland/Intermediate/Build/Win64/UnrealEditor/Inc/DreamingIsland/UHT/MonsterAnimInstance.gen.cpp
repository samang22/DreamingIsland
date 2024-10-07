// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DreamingIsland/Actors/MonsterAnimInstance.h"
#include "Runtime/Engine/Classes/Components/SkeletalMeshComponent.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeMonsterAnimInstance() {}

// Begin Cross Module References
DREAMINGISLAND_API UClass* Z_Construct_UClass_UMonsterAnimInstance();
DREAMINGISLAND_API UClass* Z_Construct_UClass_UMonsterAnimInstance_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UAnimInstance();
UPackage* Z_Construct_UPackage__Script_DreamingIsland();
// End Cross Module References

// Begin Class UMonsterAnimInstance
void UMonsterAnimInstance::StaticRegisterNativesUMonsterAnimInstance()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UMonsterAnimInstance);
UClass* Z_Construct_UClass_UMonsterAnimInstance_NoRegister()
{
	return UMonsterAnimInstance::StaticClass();
}
struct Z_Construct_UClass_UMonsterAnimInstance_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "HideCategories", "AnimInstance" },
		{ "IncludePath", "Actors/MonsterAnimInstance.h" },
		{ "ModuleRelativePath", "Actors/MonsterAnimInstance.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UMonsterAnimInstance>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UMonsterAnimInstance_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UAnimInstance,
	(UObject* (*)())Z_Construct_UPackage__Script_DreamingIsland,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UMonsterAnimInstance_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UMonsterAnimInstance_Statics::ClassParams = {
	&UMonsterAnimInstance::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
	0,
	0x009000A8u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UMonsterAnimInstance_Statics::Class_MetaDataParams), Z_Construct_UClass_UMonsterAnimInstance_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UMonsterAnimInstance()
{
	if (!Z_Registration_Info_UClass_UMonsterAnimInstance.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UMonsterAnimInstance.OuterSingleton, Z_Construct_UClass_UMonsterAnimInstance_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UMonsterAnimInstance.OuterSingleton;
}
template<> DREAMINGISLAND_API UClass* StaticClass<UMonsterAnimInstance>()
{
	return UMonsterAnimInstance::StaticClass();
}
UMonsterAnimInstance::UMonsterAnimInstance(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UMonsterAnimInstance);
UMonsterAnimInstance::~UMonsterAnimInstance() {}
// End Class UMonsterAnimInstance

// Begin Registration
struct Z_CompiledInDeferFile_FID_Minhyeok_DreamingIsland_DreamingIsland_Source_DreamingIsland_Actors_MonsterAnimInstance_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UMonsterAnimInstance, UMonsterAnimInstance::StaticClass, TEXT("UMonsterAnimInstance"), &Z_Registration_Info_UClass_UMonsterAnimInstance, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UMonsterAnimInstance), 1498718548U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Minhyeok_DreamingIsland_DreamingIsland_Source_DreamingIsland_Actors_MonsterAnimInstance_h_1637091243(TEXT("/Script/DreamingIsland"),
	Z_CompiledInDeferFile_FID_Minhyeok_DreamingIsland_DreamingIsland_Source_DreamingIsland_Actors_MonsterAnimInstance_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Minhyeok_DreamingIsland_DreamingIsland_Source_DreamingIsland_Actors_MonsterAnimInstance_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
