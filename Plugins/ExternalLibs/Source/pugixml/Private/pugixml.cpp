// Copyright Epic Games, Inc. All Rights Reserved.

#include "pugixml.h"
#include "Core.h"
#include "Modules/ModuleManager.h"
#include "Interfaces/IPluginManager.h"

#define LOCTEXT_NAMESPACE "FPugixmlModule"

void FPugixmlModule::StartupModule()
{
#if PLATFORM_WINDOWS
	pugi::xml_document XmlDoc;
	XmlDoc.load_string("Hello pugi!");
	UE_LOG(LogTemp, Warning, TEXT("pugixml loaded!"));
#endif
}

void FPugixmlModule::ShutdownModule()
{
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FPugixmlModule, pugixml)
