// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DreamingIsland/Data/PawnTableRow.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodePawnTableRow() {}

// Begin Cross Module References
COREUOBJECT_API UClass* Z_Construct_UClass_UClass();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FTransform();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
DREAMINGISLAND_API UScriptStruct* Z_Construct_UScriptStruct_FPawnTableRow();
ENGINE_API UClass* Z_Construct_UClass_UAnimInstance_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UAnimMontage_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UShapeComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_USkeletalMesh_NoRegister();
ENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FTableRowBase();
UPackage* Z_Construct_UPackage__Script_DreamingIsland();
// End Cross Module References

// Begin ScriptStruct FPawnTableRow
static_assert(std::is_polymorphic<FPawnTableRow>() == std::is_polymorphic<FTableRowBase>(), "USTRUCT FPawnTableRow cannot be polymorphic unless super FTableRowBase is polymorphic");
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_PawnTableRow;
class UScriptStruct* FPawnTableRow::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_PawnTableRow.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_PawnTableRow.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FPawnTableRow, (UObject*)Z_Construct_UPackage__Script_DreamingIsland(), TEXT("PawnTableRow"));
	}
	return Z_Registration_Info_UScriptStruct_PawnTableRow.OuterSingleton;
}
template<> DREAMINGISLAND_API UScriptStruct* StaticStruct<FPawnTableRow>()
{
	return FPawnTableRow::StaticStruct();
}
struct Z_Construct_UScriptStruct_FPawnTableRow_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "ModuleRelativePath", "Data/PawnTableRow.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SkeletalMesh_MetaData[] = {
		{ "Category", "Enemy" },
		{ "ModuleRelativePath", "Data/PawnTableRow.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MeshTransform_MetaData[] = {
		{ "Category", "Enemy" },
		{ "ModuleRelativePath", "Data/PawnTableRow.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AnimClass_MetaData[] = {
		{ "Category", "Enemy|Animation" },
		{ "ModuleRelativePath", "Data/PawnTableRow.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CollisionClass_MetaData[] = {
		{ "Category", "Enemy|Collision" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/* = USphereComponent::StaticClass()*/" },
#endif
		{ "ModuleRelativePath", "Data/PawnTableRow.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "= USphereComponent::StaticClass()" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CollisionSphereRadius_MetaData[] = {
		{ "Category", "Enemy|Collision" },
		{ "ModuleRelativePath", "Data/PawnTableRow.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CollisionBoxExtent_MetaData[] = {
		{ "Category", "Enemy|Collision" },
		{ "ModuleRelativePath", "Data/PawnTableRow.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CollisionCapsuleRadius_MetaData[] = {
		{ "Category", "Enemy|Collision" },
		{ "ModuleRelativePath", "Data/PawnTableRow.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CollisionCapsuleHalfHeight_MetaData[] = {
		{ "Category", "Enemy|Collision" },
		{ "ModuleRelativePath", "Data/PawnTableRow.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_HitReactMontage_MetaData[] = {
		{ "Category", "Enemy|Animation" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Animation\n" },
#endif
		{ "ModuleRelativePath", "Data/PawnTableRow.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Animation" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DieMontage_MetaData[] = {
		{ "Category", "Enemy|Animation" },
		{ "ModuleRelativePath", "Data/PawnTableRow.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SkeletalMesh;
	static const UECodeGen_Private::FStructPropertyParams NewProp_MeshTransform;
	static const UECodeGen_Private::FClassPropertyParams NewProp_AnimClass;
	static const UECodeGen_Private::FClassPropertyParams NewProp_CollisionClass;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_CollisionSphereRadius;
	static const UECodeGen_Private::FStructPropertyParams NewProp_CollisionBoxExtent;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_CollisionCapsuleRadius;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_CollisionCapsuleHalfHeight;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_HitReactMontage_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_HitReactMontage;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_DieMontage_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_DieMontage;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FPawnTableRow>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UScriptStruct_FPawnTableRow_Statics::NewProp_SkeletalMesh = { "SkeletalMesh", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FPawnTableRow, SkeletalMesh), Z_Construct_UClass_USkeletalMesh_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SkeletalMesh_MetaData), NewProp_SkeletalMesh_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FPawnTableRow_Statics::NewProp_MeshTransform = { "MeshTransform", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FPawnTableRow, MeshTransform), Z_Construct_UScriptStruct_FTransform, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MeshTransform_MetaData), NewProp_MeshTransform_MetaData) };
const UECodeGen_Private::FClassPropertyParams Z_Construct_UScriptStruct_FPawnTableRow_Statics::NewProp_AnimClass = { "AnimClass", nullptr, (EPropertyFlags)0x0014000000000001, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FPawnTableRow, AnimClass), Z_Construct_UClass_UClass, Z_Construct_UClass_UAnimInstance_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AnimClass_MetaData), NewProp_AnimClass_MetaData) };
const UECodeGen_Private::FClassPropertyParams Z_Construct_UScriptStruct_FPawnTableRow_Statics::NewProp_CollisionClass = { "CollisionClass", nullptr, (EPropertyFlags)0x0014000000000001, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FPawnTableRow, CollisionClass), Z_Construct_UClass_UClass, Z_Construct_UClass_UShapeComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CollisionClass_MetaData), NewProp_CollisionClass_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FPawnTableRow_Statics::NewProp_CollisionSphereRadius = { "CollisionSphereRadius", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FPawnTableRow, CollisionSphereRadius), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CollisionSphereRadius_MetaData), NewProp_CollisionSphereRadius_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FPawnTableRow_Statics::NewProp_CollisionBoxExtent = { "CollisionBoxExtent", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FPawnTableRow, CollisionBoxExtent), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CollisionBoxExtent_MetaData), NewProp_CollisionBoxExtent_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FPawnTableRow_Statics::NewProp_CollisionCapsuleRadius = { "CollisionCapsuleRadius", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FPawnTableRow, CollisionCapsuleRadius), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CollisionCapsuleRadius_MetaData), NewProp_CollisionCapsuleRadius_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FPawnTableRow_Statics::NewProp_CollisionCapsuleHalfHeight = { "CollisionCapsuleHalfHeight", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FPawnTableRow, CollisionCapsuleHalfHeight), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CollisionCapsuleHalfHeight_MetaData), NewProp_CollisionCapsuleHalfHeight_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UScriptStruct_FPawnTableRow_Statics::NewProp_HitReactMontage_Inner = { "HitReactMontage", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UClass_UAnimMontage_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FPawnTableRow_Statics::NewProp_HitReactMontage = { "HitReactMontage", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FPawnTableRow, HitReactMontage), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_HitReactMontage_MetaData), NewProp_HitReactMontage_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UScriptStruct_FPawnTableRow_Statics::NewProp_DieMontage_Inner = { "DieMontage", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UClass_UAnimMontage_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FPawnTableRow_Statics::NewProp_DieMontage = { "DieMontage", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FPawnTableRow, DieMontage), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DieMontage_MetaData), NewProp_DieMontage_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FPawnTableRow_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FPawnTableRow_Statics::NewProp_SkeletalMesh,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FPawnTableRow_Statics::NewProp_MeshTransform,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FPawnTableRow_Statics::NewProp_AnimClass,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FPawnTableRow_Statics::NewProp_CollisionClass,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FPawnTableRow_Statics::NewProp_CollisionSphereRadius,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FPawnTableRow_Statics::NewProp_CollisionBoxExtent,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FPawnTableRow_Statics::NewProp_CollisionCapsuleRadius,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FPawnTableRow_Statics::NewProp_CollisionCapsuleHalfHeight,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FPawnTableRow_Statics::NewProp_HitReactMontage_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FPawnTableRow_Statics::NewProp_HitReactMontage,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FPawnTableRow_Statics::NewProp_DieMontage_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FPawnTableRow_Statics::NewProp_DieMontage,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FPawnTableRow_Statics::PropPointers) < 2048);
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FPawnTableRow_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_DreamingIsland,
	Z_Construct_UScriptStruct_FTableRowBase,
	&NewStructOps,
	"PawnTableRow",
	Z_Construct_UScriptStruct_FPawnTableRow_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FPawnTableRow_Statics::PropPointers),
	sizeof(FPawnTableRow),
	alignof(FPawnTableRow),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FPawnTableRow_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FPawnTableRow_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FPawnTableRow()
{
	if (!Z_Registration_Info_UScriptStruct_PawnTableRow.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_PawnTableRow.InnerSingleton, Z_Construct_UScriptStruct_FPawnTableRow_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_PawnTableRow.InnerSingleton;
}
// End ScriptStruct FPawnTableRow

// Begin Registration
struct Z_CompiledInDeferFile_FID_Minhyeok_DreamingIsland_DreamingIsland_Source_DreamingIsland_Data_PawnTableRow_h_Statics
{
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FPawnTableRow::StaticStruct, Z_Construct_UScriptStruct_FPawnTableRow_Statics::NewStructOps, TEXT("PawnTableRow"), &Z_Registration_Info_UScriptStruct_PawnTableRow, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FPawnTableRow), 664076152U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Minhyeok_DreamingIsland_DreamingIsland_Source_DreamingIsland_Data_PawnTableRow_h_3119217004(TEXT("/Script/DreamingIsland"),
	nullptr, 0,
	Z_CompiledInDeferFile_FID_Minhyeok_DreamingIsland_DreamingIsland_Source_DreamingIsland_Data_PawnTableRow_h_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Minhyeok_DreamingIsland_DreamingIsland_Source_DreamingIsland_Data_PawnTableRow_h_Statics::ScriptStructInfo),
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
