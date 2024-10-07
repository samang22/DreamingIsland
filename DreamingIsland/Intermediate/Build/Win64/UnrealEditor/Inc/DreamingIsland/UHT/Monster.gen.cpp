// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DreamingIsland/Actors/Monster.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeMonster() {}

// Begin Cross Module References
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FTransform();
DREAMINGISLAND_API UClass* Z_Construct_UClass_AMonster();
DREAMINGISLAND_API UClass* Z_Construct_UClass_AMonster_NoRegister();
DREAMINGISLAND_API UClass* Z_Construct_UClass_UMonsterDataAsset();
DREAMINGISLAND_API UClass* Z_Construct_UClass_UMonsterDataAsset_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_AActor();
ENGINE_API UClass* Z_Construct_UClass_UDataAsset();
ENGINE_API UClass* Z_Construct_UClass_USkeletalMesh_NoRegister();
UPackage* Z_Construct_UPackage__Script_DreamingIsland();
// End Cross Module References

// Begin Class UMonsterDataAsset
void UMonsterDataAsset::StaticRegisterNativesUMonsterDataAsset()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UMonsterDataAsset);
UClass* Z_Construct_UClass_UMonsterDataAsset_NoRegister()
{
	return UMonsterDataAsset::StaticClass();
}
struct Z_Construct_UClass_UMonsterDataAsset_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "Actors/Monster.h" },
		{ "ModuleRelativePath", "Actors/Monster.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SkeletalMesh_MetaData[] = {
		{ "Category", "SkeletalMeshComponent" },
		{ "ModuleRelativePath", "Actors/Monster.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SkeletalMeshTransform_MetaData[] = {
		{ "Category", "SkeletalMeshComponent" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "//UPROPERTY(EditAnywhere, Category = \"SkeletalMeshComponent\")\n//TSubclassOf<UBaisicCharacterAnimInstance> AnimClass = UBaisicCharacterAnimInstance::StaticClass();\n" },
#endif
		{ "ModuleRelativePath", "Actors/Monster.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "UPROPERTY(EditAnywhere, Category = \"SkeletalMeshComponent\")\nTSubclassOf<UBaisicCharacterAnimInstance> AnimClass = UBaisicCharacterAnimInstance::StaticClass();" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SkeletalMesh;
	static const UECodeGen_Private::FStructPropertyParams NewProp_SkeletalMeshTransform;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UMonsterDataAsset>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UMonsterDataAsset_Statics::NewProp_SkeletalMesh = { "SkeletalMesh", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UMonsterDataAsset, SkeletalMesh), Z_Construct_UClass_USkeletalMesh_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SkeletalMesh_MetaData), NewProp_SkeletalMesh_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UMonsterDataAsset_Statics::NewProp_SkeletalMeshTransform = { "SkeletalMeshTransform", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UMonsterDataAsset, SkeletalMeshTransform), Z_Construct_UScriptStruct_FTransform, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SkeletalMeshTransform_MetaData), NewProp_SkeletalMeshTransform_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UMonsterDataAsset_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMonsterDataAsset_Statics::NewProp_SkeletalMesh,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMonsterDataAsset_Statics::NewProp_SkeletalMeshTransform,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UMonsterDataAsset_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UMonsterDataAsset_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UDataAsset,
	(UObject* (*)())Z_Construct_UPackage__Script_DreamingIsland,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UMonsterDataAsset_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UMonsterDataAsset_Statics::ClassParams = {
	&UMonsterDataAsset::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_UMonsterDataAsset_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_UMonsterDataAsset_Statics::PropPointers),
	0,
	0x000000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UMonsterDataAsset_Statics::Class_MetaDataParams), Z_Construct_UClass_UMonsterDataAsset_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UMonsterDataAsset()
{
	if (!Z_Registration_Info_UClass_UMonsterDataAsset.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UMonsterDataAsset.OuterSingleton, Z_Construct_UClass_UMonsterDataAsset_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UMonsterDataAsset.OuterSingleton;
}
template<> DREAMINGISLAND_API UClass* StaticClass<UMonsterDataAsset>()
{
	return UMonsterDataAsset::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UMonsterDataAsset);
UMonsterDataAsset::~UMonsterDataAsset() {}
// End Class UMonsterDataAsset

// Begin Class AMonster
void AMonster::StaticRegisterNativesAMonster()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AMonster);
UClass* Z_Construct_UClass_AMonster_NoRegister()
{
	return AMonster::StaticClass();
}
struct Z_Construct_UClass_AMonster_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "Actors/Monster.h" },
		{ "ModuleRelativePath", "Actors/Monster.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MonsterDataAsset_MetaData[] = {
		{ "Category", "Monster" },
		{ "ModuleRelativePath", "Actors/Monster.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_MonsterDataAsset;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AMonster>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AMonster_Statics::NewProp_MonsterDataAsset = { "MonsterDataAsset", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMonster, MonsterDataAsset), Z_Construct_UClass_UMonsterDataAsset_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MonsterDataAsset_MetaData), NewProp_MonsterDataAsset_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AMonster_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMonster_Statics::NewProp_MonsterDataAsset,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AMonster_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_AMonster_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AActor,
	(UObject* (*)())Z_Construct_UPackage__Script_DreamingIsland,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AMonster_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AMonster_Statics::ClassParams = {
	&AMonster::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_AMonster_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_AMonster_Statics::PropPointers),
	0,
	0x009000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AMonster_Statics::Class_MetaDataParams), Z_Construct_UClass_AMonster_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_AMonster()
{
	if (!Z_Registration_Info_UClass_AMonster.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AMonster.OuterSingleton, Z_Construct_UClass_AMonster_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AMonster.OuterSingleton;
}
template<> DREAMINGISLAND_API UClass* StaticClass<AMonster>()
{
	return AMonster::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(AMonster);
AMonster::~AMonster() {}
// End Class AMonster

// Begin Registration
struct Z_CompiledInDeferFile_FID_Minhyeok_DreamingIsland_DreamingIsland_Source_DreamingIsland_Actors_Monster_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UMonsterDataAsset, UMonsterDataAsset::StaticClass, TEXT("UMonsterDataAsset"), &Z_Registration_Info_UClass_UMonsterDataAsset, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UMonsterDataAsset), 112374547U) },
		{ Z_Construct_UClass_AMonster, AMonster::StaticClass, TEXT("AMonster"), &Z_Registration_Info_UClass_AMonster, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AMonster), 1511812794U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Minhyeok_DreamingIsland_DreamingIsland_Source_DreamingIsland_Actors_Monster_h_3891734248(TEXT("/Script/DreamingIsland"),
	Z_CompiledInDeferFile_FID_Minhyeok_DreamingIsland_DreamingIsland_Source_DreamingIsland_Actors_Monster_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Minhyeok_DreamingIsland_DreamingIsland_Source_DreamingIsland_Actors_Monster_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
