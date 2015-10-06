// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	C++ class header boilerplate exported from UnrealHeaderTool.
	This is automatically generated by the tools.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "ObjectBase.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef GODZILLA_GodzillaCharacter_generated_h
#error "GodzillaCharacter.generated.h already included, missing '#pragma once' in GodzillaCharacter.h"
#endif
#define GODZILLA_GodzillaCharacter_generated_h

#define Godzilla_Source_Godzilla_GodzillaCharacter_h_9_RPC_WRAPPERS
#define Godzilla_Source_Godzilla_GodzillaCharacter_h_9_RPC_WRAPPERS_NO_PURE_DECLS
#define Godzilla_Source_Godzilla_GodzillaCharacter_h_9_INCLASS_NO_PURE_DECLS \
	private: \
	static void StaticRegisterNativesAGodzillaCharacter(); \
	friend GODZILLA_API class UClass* Z_Construct_UClass_AGodzillaCharacter(); \
	public: \
	DECLARE_CLASS(AGodzillaCharacter, ACharacter, COMPILED_IN_FLAGS(0), 0, Godzilla, NO_API) \
	DECLARE_SERIALIZER(AGodzillaCharacter) \
	/** Indicates whether the class is compiled into the engine */    enum {IsIntrinsic=COMPILED_IN_INTRINSIC}; \
	virtual UObject* _getUObject() const override { return const_cast<AGodzillaCharacter*>(this); }


#define Godzilla_Source_Godzilla_GodzillaCharacter_h_9_INCLASS \
	private: \
	static void StaticRegisterNativesAGodzillaCharacter(); \
	friend GODZILLA_API class UClass* Z_Construct_UClass_AGodzillaCharacter(); \
	public: \
	DECLARE_CLASS(AGodzillaCharacter, ACharacter, COMPILED_IN_FLAGS(0), 0, Godzilla, NO_API) \
	DECLARE_SERIALIZER(AGodzillaCharacter) \
	/** Indicates whether the class is compiled into the engine */    enum {IsIntrinsic=COMPILED_IN_INTRINSIC}; \
	virtual UObject* _getUObject() const override { return const_cast<AGodzillaCharacter*>(this); }


#define Godzilla_Source_Godzilla_GodzillaCharacter_h_9_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AGodzillaCharacter(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AGodzillaCharacter) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AGodzillaCharacter); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AGodzillaCharacter); \
private: \
	/** Private copy-constructor, should never be used */ \
	NO_API AGodzillaCharacter(const AGodzillaCharacter& InCopy); \
public:


#define Godzilla_Source_Godzilla_GodzillaCharacter_h_9_ENHANCED_CONSTRUCTORS \
private: \
	/** Private copy-constructor, should never be used */ \
	NO_API AGodzillaCharacter(const AGodzillaCharacter& InCopy); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AGodzillaCharacter); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AGodzillaCharacter); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AGodzillaCharacter)


#define Godzilla_Source_Godzilla_GodzillaCharacter_h_6_PROLOG
#define Godzilla_Source_Godzilla_GodzillaCharacter_h_9_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Godzilla_Source_Godzilla_GodzillaCharacter_h_9_RPC_WRAPPERS \
	Godzilla_Source_Godzilla_GodzillaCharacter_h_9_INCLASS \
	Godzilla_Source_Godzilla_GodzillaCharacter_h_9_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define Godzilla_Source_Godzilla_GodzillaCharacter_h_9_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Godzilla_Source_Godzilla_GodzillaCharacter_h_9_RPC_WRAPPERS_NO_PURE_DECLS \
	Godzilla_Source_Godzilla_GodzillaCharacter_h_9_INCLASS_NO_PURE_DECLS \
	Godzilla_Source_Godzilla_GodzillaCharacter_h_9_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID Godzilla_Source_Godzilla_GodzillaCharacter_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
