// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DreamingIsland/Animation/MonsterAnimInstance.h"
#include "Runtime/Engine/Classes/Components/SkeletalMeshComponent.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeMonsterAnimInstance() {}

// Begin Cross Module References
DREAMINGISLAND_API UClass* Z_Construct_UClass_UMonsterAnimInstance();
DREAMINGISLAND_API UClass* Z_Construct_UClass_UMonsterAnimInstance_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UAnimInstance();
ENGINE_API UClass* Z_Construct_UClass_UPawnMovementComponent_NoRegister();
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
		{ "IncludePath", "Animation/MonsterAnimInstance.h" },
		{ "ModuleRelativePath", "Animation/MonsterAnimInstance.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MovementComponent_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Animation/MonsterAnimInstance.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Speed_MetaData[] = {
		{ "Category", "MonsterAnimInstance" },
		{ "ModuleRelativePath", "Animation/MonsterAnimInstance.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_MovementComponent;
	static const UECodeGen_Private::FDoublePropertyParams NewProp_Speed;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UMonsterAnimInstance>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UMonsterAnimInstance_Statics::NewProp_MovementComponent = { "MovementComponent", nullptr, (EPropertyFlags)0x0020080000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UMonsterAnimInstance, MovementComponent), Z_Construct_UClass_UPawnMovementComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MovementComponent_MetaData), NewProp_MovementComponent_MetaData) };
const UECodeGen_Private::FDoublePropertyParams Z_Construct_UClass_UMonsterAnimInstance_Statics::NewProp_Speed = { "Speed", nullptr, (EPropertyFlags)0x0020080000000014, UECodeGen_Private::EPropertyGenFlags::Double, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UMonsterAnimInstance, Speed), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Speed_MetaData), NewProp_Speed_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UMonsterAnimInstance_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMonsterAnimInstance_Statics::NewProp_MovementComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMonsterAnimInstance_Statics::NewProp_Speed,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UMonsterAnimInstance_Statics::PropPointers) < 2048);
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
	Z_Construct_UClass_UMonsterAnimInstance_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_UMonsterAnimInstance_Statics::PropPointers),
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
struct Z_CompiledInDeferFile_FID_Minhyeok_DreamingIsland_DreamingIsland_Source_DreamingIsland_Animation_MonsterAnimInstance_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UMonsterAnimInstance, UMonsterAnimInstance::StaticClass, TEXT("UMonsterAnimInstance"), &Z_Registration_Info_UClass_UMonsterAnimInstance, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UMonsterAnimInstance), 1359681352U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Minhyeok_DreamingIsland_DreamingIsland_Source_DreamingIsland_Animation_MonsterAnimInstance_h_3171913712(TEXT("/Script/DreamingIsland"),
	Z_CompiledInDeferFile_FID_Minhyeok_DreamingIsland_DreamingIsland_Source_DreamingIsland_Animation_MonsterAnimInstance_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Minhyeok_DreamingIsland_DreamingIsland_Source_DreamingIsland_Animation_MonsterAnimInstance_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
