﻿#include "CSGeneratedStructBuilder.h"
#include "CSMetaDataUtils.h"
#include "CSTypeRegistry.h"
#include "UnrealSharpCore/TypeGenerator/CSScriptStruct.h"
#include "UnrealSharpCore/TypeGenerator/Factories/CSPropertyFactory.h"

#if WITH_EDITOR
#include "UserDefinedStructure/UserDefinedStructEditorData.h"
#endif

void FCSGeneratedStructBuilder::StartBuildingType()
{
	FCSPropertyFactory::GeneratePropertiesForType(Field, TypeMetaData->Properties);
	
#if WITH_EDITOR
	Field->EditorData = NewObject<UUserDefinedStructEditorData>(Field, NAME_None, RF_Transactional);
#endif
		
	Field->Status = UDSS_UpToDate;
	if (!Field->Guid.IsValid())
	{
		Field->Guid = FGuid::NewGuid();
	}
	
	Field->Bind();
	Field->StaticLink(true);
	Field->RecreateDefaults();
	
	RegisterFieldToLoader(ENotifyRegistrationType::NRT_Struct);
}

void FCSGeneratedStructBuilder::NewField(UCSScriptStruct* OldField, UCSScriptStruct* NewField)
{
	OldField->StructFlags = static_cast<EStructFlags>(OldField->StructFlags | STRUCT_NewerVersionExists);
	NewField->Guid = OldField->Guid;
	FCSTypeRegistry::Get().GetOnNewStructEvent().Broadcast(OldField, NewField);
}
