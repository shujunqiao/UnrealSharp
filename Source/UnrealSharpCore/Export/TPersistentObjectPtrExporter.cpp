﻿#include "TPersistentObjectPtrExporter.h"
#include "UnrealSharpCore/CSManager.h"

void UTPersistentObjectPtrExporter::ExportFunctions(FRegisterExportedFunction RegisterExportedFunction)
{
	EXPORT_FUNCTION(FromObject)
	EXPORT_FUNCTION(Get)
	EXPORT_FUNCTION(GetNativePointer)
	EXPORT_FUNCTION(GetUniqueID)
	EXPORT_FUNCTION(FromSoftObjectPath)
}

void UTPersistentObjectPtrExporter::FromObject(TPersistentObjectPtr<FSoftObjectPath>* Path, UObject* InObject)
{
	*Path = InObject;
}

void UTPersistentObjectPtrExporter::FromSoftObjectPath(TPersistentObjectPtr<FSoftObjectPath>* Path, const FSoftObjectPath* SoftObjectPath)
{
	*Path = *SoftObjectPath;
}

void* UTPersistentObjectPtrExporter::Get(TPersistentObjectPtr<FSoftObjectPath>* Path)
{
	UObject* Object = Path->Get();
	return UCSManager::Get().FindManagedObject(Object).GetPointer();
}

void* UTPersistentObjectPtrExporter::GetNativePointer(TPersistentObjectPtr<FSoftObjectPath>* Path)
{
	return Path->Get();
}

void* UTPersistentObjectPtrExporter::GetUniqueID(TPersistentObjectPtr<FSoftObjectPath>* Path)
{
	return &Path->GetUniqueID();
}

