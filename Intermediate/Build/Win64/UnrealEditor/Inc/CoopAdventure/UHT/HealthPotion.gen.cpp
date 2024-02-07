// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "CoopAdventure/HealthPotion.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeHealthPotion() {}
// Cross Module References
	COOPADVENTURE_API UClass* Z_Construct_UClass_AHealthPotion();
	COOPADVENTURE_API UClass* Z_Construct_UClass_AHealthPotion_NoRegister();
	COOPADVENTURE_API UClass* Z_Construct_UClass_AItem();
	UPackage* Z_Construct_UPackage__Script_CoopAdventure();
// End Cross Module References
	void AHealthPotion::StaticRegisterNativesAHealthPotion()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AHealthPotion);
	UClass* Z_Construct_UClass_AHealthPotion_NoRegister()
	{
		return AHealthPotion::StaticClass();
	}
	struct Z_Construct_UClass_AHealthPotion_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_HealthValue_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_HealthValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AHealthPotion_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AItem,
		(UObject* (*)())Z_Construct_UPackage__Script_CoopAdventure,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AHealthPotion_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AHealthPotion_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "HealthPotion.h" },
		{ "ModuleRelativePath", "HealthPotion.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AHealthPotion_Statics::NewProp_HealthValue_MetaData[] = {
		{ "Category", "HealthPotion" },
		{ "ModuleRelativePath", "HealthPotion.h" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AHealthPotion_Statics::NewProp_HealthValue = { "HealthValue", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AHealthPotion, HealthValue), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AHealthPotion_Statics::NewProp_HealthValue_MetaData), Z_Construct_UClass_AHealthPotion_Statics::NewProp_HealthValue_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AHealthPotion_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AHealthPotion_Statics::NewProp_HealthValue,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_AHealthPotion_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AHealthPotion>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_AHealthPotion_Statics::ClassParams = {
		&AHealthPotion::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_AHealthPotion_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_AHealthPotion_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AHealthPotion_Statics::Class_MetaDataParams), Z_Construct_UClass_AHealthPotion_Statics::Class_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AHealthPotion_Statics::PropPointers) < 2048);
	UClass* Z_Construct_UClass_AHealthPotion()
	{
		if (!Z_Registration_Info_UClass_AHealthPotion.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AHealthPotion.OuterSingleton, Z_Construct_UClass_AHealthPotion_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_AHealthPotion.OuterSingleton;
	}
	template<> COOPADVENTURE_API UClass* StaticClass<AHealthPotion>()
	{
		return AHealthPotion::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(AHealthPotion);
	AHealthPotion::~AHealthPotion() {}
	struct Z_CompiledInDeferFile_FID_Users_Owner_Documents_Unreal_Projects_CoopAdventure_Source_CoopAdventure_HealthPotion_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Owner_Documents_Unreal_Projects_CoopAdventure_Source_CoopAdventure_HealthPotion_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_AHealthPotion, AHealthPotion::StaticClass, TEXT("AHealthPotion"), &Z_Registration_Info_UClass_AHealthPotion, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AHealthPotion), 3653367979U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Owner_Documents_Unreal_Projects_CoopAdventure_Source_CoopAdventure_HealthPotion_h_2719754833(TEXT("/Script/CoopAdventure"),
		Z_CompiledInDeferFile_FID_Users_Owner_Documents_Unreal_Projects_CoopAdventure_Source_CoopAdventure_HealthPotion_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_Owner_Documents_Unreal_Projects_CoopAdventure_Source_CoopAdventure_HealthPotion_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
