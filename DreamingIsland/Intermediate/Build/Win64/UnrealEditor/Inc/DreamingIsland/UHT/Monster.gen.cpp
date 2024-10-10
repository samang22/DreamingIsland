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
COREUOBJECT_API UClass* Z_Construct_UClass_UClass();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FTransform();
DREAMINGISLAND_API UClass* Z_Construct_UClass_AMonster();
DREAMINGISLAND_API UClass* Z_Construct_UClass_AMonster_NoRegister();
DREAMINGISLAND_API UClass* Z_Construct_UClass_UMonsterAnimInstance_NoRegister();
DREAMINGISLAND_API UClass* Z_Construct_UClass_UMonsterDataAsset();
DREAMINGISLAND_API UClass* Z_Construct_UClass_UMonsterDataAsset_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_APawn();
ENGINE_API UClass* Z_Construct_UClass_UDataAsset();
ENGINE_API UClass* Z_Construct_UClass_UFloatingPawnMovement_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UShapeComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_USkeletalMesh_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_USkeletalMeshComponent_NoRegister();
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
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AnimClass_MetaData[] = {
		{ "Category", "SkeletalMeshComponent" },
		{ "ModuleRelativePath", "Actors/Monster.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SkeletalMeshTransform_MetaData[] = {
		{ "Category", "SkeletalMeshComponent" },
		{ "ModuleRelativePath", "Actors/Monster.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SkeletalMesh;
	static const UECodeGen_Private::FClassPropertyParams NewProp_AnimClass;
	static const UECodeGen_Private::FStructPropertyParams NewProp_SkeletalMeshTransform;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UMonsterDataAsset>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UMonsterDataAsset_Statics::NewProp_SkeletalMesh = { "SkeletalMesh", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UMonsterDataAsset, SkeletalMesh), Z_Construct_UClass_USkeletalMesh_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SkeletalMesh_MetaData), NewProp_SkeletalMesh_MetaData) };
const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_UMonsterDataAsset_Statics::NewProp_AnimClass = { "AnimClass", nullptr, (EPropertyFlags)0x0014000000000001, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UMonsterDataAsset, AnimClass), Z_Construct_UClass_UClass, Z_Construct_UClass_UMonsterAnimInstance_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AnimClass_MetaData), NewProp_AnimClass_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UMonsterDataAsset_Statics::NewProp_SkeletalMeshTransform = { "SkeletalMeshTransform", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UMonsterDataAsset, SkeletalMeshTransform), Z_Construct_UScriptStruct_FTransform, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SkeletalMeshTransform_MetaData), NewProp_SkeletalMeshTransform_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UMonsterDataAsset_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMonsterDataAsset_Statics::NewProp_SkeletalMesh,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMonsterDataAsset_Statics::NewProp_AnimClass,
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

// Begin Class AMonster Function OnDie
struct Z_Construct_UFunction_AMonster_OnDie_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Actors/Monster.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AMonster_OnDie_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AMonster, nullptr, "OnDie", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AMonster_OnDie_Statics::Function_MetaDataParams), Z_Construct_UFunction_AMonster_OnDie_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_AMonster_OnDie()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AMonster_OnDie_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AMonster::execOnDie)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnDie();
	P_NATIVE_END;
}
// End Class AMonster Function OnDie

// Begin Class AMonster
void AMonster::StaticRegisterNativesAMonster()
{
	UClass* Class = AMonster::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "OnDie", &AMonster::execOnDie },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
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
#if !UE_BUILD_SHIPPING
		{ "Comment", "//class FDataTableRowHandle;\n" },
#endif
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "Actors/Monster.h" },
		{ "ModuleRelativePath", "Actors/Monster.h" },
		{ "ObjectInitializerConstructorDeclared", "" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "class FDataTableRowHandle;" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CollisionComponent_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xec\x98\xb5\xec\x85\x98\xec\x97\x90 \xeb\x94\xb0\xeb\x9d\xbc \xec\x83\x9d\xec\x84\xb1\xeb\x90\x98\xea\xb3\xa0 Root\xeb\xa1\x9c \xec\xa7\x80\xec\xa0\x95 \xeb\x90\xa9\xeb\x8b\x88\xeb\x8b\xa4.\n" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Actors/Monster.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xec\x98\xb5\xec\x85\x98\xec\x97\x90 \xeb\x94\xb0\xeb\x9d\xbc \xec\x83\x9d\xec\x84\xb1\xeb\x90\x98\xea\xb3\xa0 Root\xeb\xa1\x9c \xec\xa7\x80\xec\xa0\x95 \xeb\x90\xa9\xeb\x8b\x88\xeb\x8b\xa4." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SkeletalMeshComponent_MetaData[] = {
		{ "Category", "Monster" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Actors/Monster.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MovementComponent_MetaData[] = {
		{ "Category", "Monster" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Actors/Monster.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_CollisionComponent;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SkeletalMeshComponent;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_MovementComponent;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_AMonster_OnDie, "OnDie" }, // 2180066435
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AMonster>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AMonster_Statics::NewProp_CollisionComponent = { "CollisionComponent", nullptr, (EPropertyFlags)0x0124080000080008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMonster, CollisionComponent), Z_Construct_UClass_UShapeComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CollisionComponent_MetaData), NewProp_CollisionComponent_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AMonster_Statics::NewProp_SkeletalMeshComponent = { "SkeletalMeshComponent", nullptr, (EPropertyFlags)0x01240800000a0009, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMonster, SkeletalMeshComponent), Z_Construct_UClass_USkeletalMeshComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SkeletalMeshComponent_MetaData), NewProp_SkeletalMeshComponent_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AMonster_Statics::NewProp_MovementComponent = { "MovementComponent", nullptr, (EPropertyFlags)0x00200800000a0009, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMonster, MovementComponent), Z_Construct_UClass_UFloatingPawnMovement_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MovementComponent_MetaData), NewProp_MovementComponent_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AMonster_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMonster_Statics::NewProp_CollisionComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMonster_Statics::NewProp_SkeletalMeshComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMonster_Statics::NewProp_MovementComponent,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AMonster_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_AMonster_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_APawn,
	(UObject* (*)())Z_Construct_UPackage__Script_DreamingIsland,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AMonster_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AMonster_Statics::ClassParams = {
	&AMonster::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_AMonster_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
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
		{ Z_Construct_UClass_UMonsterDataAsset, UMonsterDataAsset::StaticClass, TEXT("UMonsterDataAsset"), &Z_Registration_Info_UClass_UMonsterDataAsset, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UMonsterDataAsset), 323215599U) },
		{ Z_Construct_UClass_AMonster, AMonster::StaticClass, TEXT("AMonster"), &Z_Registration_Info_UClass_AMonster, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AMonster), 2046080733U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Minhyeok_DreamingIsland_DreamingIsland_Source_DreamingIsland_Actors_Monster_h_3041932247(TEXT("/Script/DreamingIsland"),
	Z_CompiledInDeferFile_FID_Minhyeok_DreamingIsland_DreamingIsland_Source_DreamingIsland_Actors_Monster_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Minhyeok_DreamingIsland_DreamingIsland_Source_DreamingIsland_Actors_Monster_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
