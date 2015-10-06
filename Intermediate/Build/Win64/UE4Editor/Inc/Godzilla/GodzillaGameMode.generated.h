// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	C++ class header boilerplate exported from UnrealHeaderTool.
	This is automatically generated by the tools.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "ObjectBase.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef GODZILLA_GodzillaGameMode_generated_h
#error "GodzillaGameMode.generated.h already included, missing '#pragma once' in GodzillaGameMode.h"
#endif
#define GODZILLA_GodzillaGameMode_generated_h

#define Godzilla_Source_Godzilla_GodzillaGameMode_h_9_RPC_WRAPPERS
#define Godzilla_Source_Godzilla_GodzillaGameMode_h_9_RPC_WRAPPERS_NO_PURE_DECLS
#define Godzilla_Source_Godzilla_GodzillaGameMode_h_9_INCLASS_NO_PURE_DECLS \
	private: \
	static void StaticRegisterNativesAGodzillaGameMode(); \
	friend GODZILLA_API class UClass* Z_Construct_UClass_AGodzillaGameMode(); \
	public: \
	DECLARE_CLASS(AGodzillaGameMode, AGameMode, COMPILED_IN_FLAGS(0 | CLASS_Transient | CLASS_Config), 0, Godzilla, GODZILLA_API) \
	DECLARE_SERIALIZER(AGodzillaGameMode) \
	/** Indicates whether the class is compiled into the engine */    enum {IsIntrinsic=COMPILED_IN_INTRINSIC}; \
	virtual UObject* _getUObject() const override { return const_cast<AGodzillaGameMode*>(this); }


#define Godzilla_Source_Godzilla_GodzillaGameMode_h_9_INCLASS \
	private: \
	static void StaticRegisterNativesAGodzillaGameMode(); \
	friend GODZILLA_API class UClass* Z_Construct_UClass_AGodzillaGameMode(); \
	public: \
	DECLARE_CLASS(AGodzillaGameMode, AGameMode, COMPILED_IN_FLAGS(0 | CLASS_Transient | CLASS_Config), 0, Godzilla, GODZILLA_API) \
	DECLARE_SERIALIZER(AGodzillaGameMode) \
	/** Indicates whether the class is compiled into the engine */    enum {IsIntrinsic=COMPILED_IN_INTRINSIC}; \
	virtual UObject* _getUObject() const override { return const_cast<AGodzillaGameMode*>(this); }


#define Godzilla_Source_Godzilla_GodzillaGameMode_h_9_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	GODZILLA_API AGodzillaGameMode(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AGodzillaGameMode) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(GODZILLA_API, AGodzillaGameMode); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AGodzillaGameMode); \
private: \
	/** Private copy-constructor, should never be used */ \
	GODZILLA_API AGodzillaGameMode(const AGodzillaGameMode& InCopy); \
public:


#define Godzilla_Source_Godzilla_GodzillaGameMode_h_9_ENHANCED_CONSTRUCTORS \
private: \
	/** Private copy-constructor, should never be used */ \
	GODZILLA_API AGodzillaGameMode(const AGodzillaGameMode& InCopy); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(GODZILLA_API, AGodzillaGameMode); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AGodzillaGameMode); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AGodzillaGameMode)


#define Godzilla_Source_Godzilla_GodzillaGameMode_h_6_PROLOG
#define Godzilla_Source_Godzilla_GodzillaGameMode_h_9_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Godzilla_Source_Godzilla_GodzillaGameMode_h_9_RPC_WRAPPERS \
	Godzilla_Source_Godzilla_GodzillaGameMode_h_9_INCLASS \
	Godzilla_Source_Godzilla_GodzillaGameMode_h_9_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define Godzilla_Source_Godzilla_GodzillaGameMode_h_9_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Godzilla_Source_Godzilla_GodzillaGameMode_h_9_RPC_WRAPPERS_NO_PURE_DECLS \
	Godzilla_Source_Godzilla_GodzillaGameMode_h_9_INCLASS_NO_PURE_DECLS \
	Godzilla_Source_Godzilla_GodzillaGameMode_h_9_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID Godzilla_Source_Godzilla_GodzillaGameMode_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS