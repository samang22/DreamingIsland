// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DreamingIsland/Actors/Monsters/Albatoss.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeAlbatoss() {}

// Begin Cross Module References
DREAMINGISLAND_API UClass* Z_Construct_UClass_AAlbatoss();
DREAMINGISLAND_API UClass* Z_Construct_UClass_AAlbatoss_NoRegister();
DREAMINGISLAND_API UClass* Z_Construct_UClass_AMonster();
UPackage* Z_Construct_UPackage__Script_DreamingIsland();
// End Cross Module References

// Begin Class AAlbatoss
void AAlbatoss::StaticRegisterNativesAAlbatoss()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AAlbatoss);
UClass* Z_Construct_UClass_AAlbatoss_NoRegister()
{
	return AAlbatoss::StaticClass();
}
struct Z_Construct_UClass_AAlbatoss_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "Actors/Monsters/Albatoss.h" },
		{ "ModuleRelativePath", "Actors/Monsters/Albatoss.h" },
		{ "ObjectInitializerConstructorDeclared", "" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AAlbatoss>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_AAlbatoss_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AMonster,
	(UObject* (*)())Z_Construct_UPackage__Script_DreamingIsland,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AAlbatoss_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AAlbatoss_Statics::ClassParams = {
	&AAlbatoss::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
	0,
	0x009000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AAlbatoss_Statics::Class_MetaDataParams), Z_Construct_UClass_AAlbatoss_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_AAlbatoss()
{
	if (!Z_Registration_Info_UClass_AAlbatoss.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AAlbatoss.OuterSingleton, Z_Construct_UClass_AAlbatoss_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AAlbatoss.OuterSingleton;
}
template<> DREAMINGISLAND_API UClass* StaticClass<AAlbatoss>()
{
	return AAlbatoss::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(AAlbatoss);
AAlbatoss::~AAlbatoss() {}
// End Class AAlbatoss

// Begin Registration
struct Z_CompiledInDeferFile_FID_Minhyeok_DreamingIsland_DreamingIsland_Source_DreamingIsland_Actors_Monsters_Albatoss_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AAlbatoss, AAlbatoss::StaticClass, TEXT("AAlbatoss"), &Z_Registration_Info_UClass_AAlbatoss, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AAlbatoss), 1651964509U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Minhyeok_DreamingIsland_DreamingIsland_Source_DreamingIsland_Actors_Monsters_Albatoss_h_1448776511(TEXT("/Script/DreamingIsland"),
	Z_CompiledInDeferFile_FID_Minhyeok_DreamingIsland_DreamingIsland_Source_DreamingIsland_Actors_Monsters_Albatoss_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Minhyeok_DreamingIsland_DreamingIsland_Source_DreamingIsland_Actors_Monsters_Albatoss_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
