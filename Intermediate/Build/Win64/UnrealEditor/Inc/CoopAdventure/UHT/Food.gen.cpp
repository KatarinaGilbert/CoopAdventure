// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "CoopAdventure/Food.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeFood() {}
// Cross Module References
	COOPADVENTURE_API UClass* Z_Construct_UClass_AFood();
	COOPADVENTURE_API UClass* Z_Construct_UClass_AFood_NoRegister();
	COOPADVENTURE_API UClass* Z_Construct_UClass_AItem();
	UPackage* Z_Construct_UPackage__Script_CoopAdventure();
// End Cross Module References
	void AFood::StaticRegisterNativesAFood()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AFood);
	UClass* Z_Construct_UClass_AFood_NoRegister()
	{
		return AFood::StaticClass();
	}
	struct Z_Construct_UClass_AFood_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AFood_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AItem,
		(UObject* (*)())Z_Construct_UPackage__Script_CoopAdventure,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AFood_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AFood_Statics::Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "IncludePath", "Food.h" },
		{ "ModuleRelativePath", "Food.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AFood_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AFood>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_AFood_Statics::ClassParams = {
		&AFood::StaticClass,
		"Engine",
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
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AFood_Statics::Class_MetaDataParams), Z_Construct_UClass_AFood_Statics::Class_MetaDataParams)
	};
	UClass* Z_Construct_UClass_AFood()
	{
		if (!Z_Registration_Info_UClass_AFood.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AFood.OuterSingleton, Z_Construct_UClass_AFood_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_AFood.OuterSingleton;
	}
	template<> COOPADVENTURE_API UClass* StaticClass<AFood>()
	{
		return AFood::StaticClass();
	}
	AFood::AFood() {}
	DEFINE_VTABLE_PTR_HELPER_CTOR(AFood);
	AFood::~AFood() {}
	struct Z_CompiledInDeferFile_FID_Users_Owner_Documents_Unreal_Projects_CoopAdventure_Source_CoopAdventure_Food_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Owner_Documents_Unreal_Projects_CoopAdventure_Source_CoopAdventure_Food_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_AFood, AFood::StaticClass, TEXT("AFood"), &Z_Registration_Info_UClass_AFood, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AFood), 256870932U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Owner_Documents_Unreal_Projects_CoopAdventure_Source_CoopAdventure_Food_h_2172423738(TEXT("/Script/CoopAdventure"),
		Z_CompiledInDeferFile_FID_Users_Owner_Documents_Unreal_Projects_CoopAdventure_Source_CoopAdventure_Food_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_Owner_Documents_Unreal_Projects_CoopAdventure_Source_CoopAdventure_Food_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
