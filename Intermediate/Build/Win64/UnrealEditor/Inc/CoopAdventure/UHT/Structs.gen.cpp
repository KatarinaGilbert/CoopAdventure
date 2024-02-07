// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "CoopAdventure/Structs.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeStructs() {}
// Cross Module References
	COOPADVENTURE_API UClass* Z_Construct_UClass_AItem_NoRegister();
	COOPADVENTURE_API UScriptStruct* Z_Construct_UScriptStruct_FItemData();
	COREUOBJECT_API UClass* Z_Construct_UClass_UClass();
	ENGINE_API UClass* Z_Construct_UClass_UTexture2D_NoRegister();
	UPackage* Z_Construct_UPackage__Script_CoopAdventure();
// End Cross Module References
	static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_ItemData;
class UScriptStruct* FItemData::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_ItemData.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_ItemData.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FItemData, (UObject*)Z_Construct_UPackage__Script_CoopAdventure(), TEXT("ItemData"));
	}
	return Z_Registration_Info_UScriptStruct_ItemData.OuterSingleton;
}
template<> COOPADVENTURE_API UScriptStruct* StaticStruct<FItemData>()
{
	return FItemData::StaticStruct();
}
	struct Z_Construct_UScriptStruct_FItemData_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ItemClass_MetaData[];
#endif
		static const UECodeGen_Private::FClassPropertyParams NewProp_ItemClass;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ItemImage_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_ItemImage;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ItemCost_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_ItemCost;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UECodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FItemData_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Structs.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FItemData_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FItemData>();
	}
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FItemData_Statics::NewProp_ItemClass_MetaData[] = {
		{ "Category", "ItemData" },
		{ "ModuleRelativePath", "Structs.h" },
	};
#endif
	const UECodeGen_Private::FClassPropertyParams Z_Construct_UScriptStruct_FItemData_Statics::NewProp_ItemClass = { "ItemClass", nullptr, (EPropertyFlags)0x0014000000010005, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FItemData, ItemClass), Z_Construct_UClass_UClass, Z_Construct_UClass_AItem_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FItemData_Statics::NewProp_ItemClass_MetaData), Z_Construct_UScriptStruct_FItemData_Statics::NewProp_ItemClass_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FItemData_Statics::NewProp_ItemImage_MetaData[] = {
		{ "Category", "ItemData" },
		{ "ModuleRelativePath", "Structs.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UScriptStruct_FItemData_Statics::NewProp_ItemImage = { "ItemImage", nullptr, (EPropertyFlags)0x0010000000010005, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FItemData, ItemImage), Z_Construct_UClass_UTexture2D_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FItemData_Statics::NewProp_ItemImage_MetaData), Z_Construct_UScriptStruct_FItemData_Statics::NewProp_ItemImage_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FItemData_Statics::NewProp_ItemCost_MetaData[] = {
		{ "Category", "ItemData" },
		{ "ModuleRelativePath", "Structs.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FItemData_Statics::NewProp_ItemCost = { "ItemCost", nullptr, (EPropertyFlags)0x0010000000010005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FItemData, ItemCost), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FItemData_Statics::NewProp_ItemCost_MetaData), Z_Construct_UScriptStruct_FItemData_Statics::NewProp_ItemCost_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FItemData_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FItemData_Statics::NewProp_ItemClass,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FItemData_Statics::NewProp_ItemImage,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FItemData_Statics::NewProp_ItemCost,
	};
	const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FItemData_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_CoopAdventure,
		nullptr,
		&NewStructOps,
		"ItemData",
		Z_Construct_UScriptStruct_FItemData_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FItemData_Statics::PropPointers),
		sizeof(FItemData),
		alignof(FItemData),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FItemData_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FItemData_Statics::Struct_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FItemData_Statics::PropPointers) < 2048);
	UScriptStruct* Z_Construct_UScriptStruct_FItemData()
	{
		if (!Z_Registration_Info_UScriptStruct_ItemData.InnerSingleton)
		{
			UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_ItemData.InnerSingleton, Z_Construct_UScriptStruct_FItemData_Statics::ReturnStructParams);
		}
		return Z_Registration_Info_UScriptStruct_ItemData.InnerSingleton;
	}
	struct Z_CompiledInDeferFile_FID_Users_Owner_Documents_Unreal_Projects_CoopAdventure_Source_CoopAdventure_Structs_h_Statics
	{
		static const FStructRegisterCompiledInInfo ScriptStructInfo[];
	};
	const FStructRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Owner_Documents_Unreal_Projects_CoopAdventure_Source_CoopAdventure_Structs_h_Statics::ScriptStructInfo[] = {
		{ FItemData::StaticStruct, Z_Construct_UScriptStruct_FItemData_Statics::NewStructOps, TEXT("ItemData"), &Z_Registration_Info_UScriptStruct_ItemData, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FItemData), 3226193464U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Owner_Documents_Unreal_Projects_CoopAdventure_Source_CoopAdventure_Structs_h_1354254342(TEXT("/Script/CoopAdventure"),
		nullptr, 0,
		Z_CompiledInDeferFile_FID_Users_Owner_Documents_Unreal_Projects_CoopAdventure_Source_CoopAdventure_Structs_h_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_Owner_Documents_Unreal_Projects_CoopAdventure_Source_CoopAdventure_Structs_h_Statics::ScriptStructInfo),
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
