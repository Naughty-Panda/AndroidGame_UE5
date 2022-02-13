// Copyright Epic Games, Inc. All Rights Reserved.

#include "ExternalLibs.h"
#include "Core.h"
#include "Modules/ModuleManager.h"
#include "Interfaces/IPluginManager.h"

#define LOCTEXT_NAMESPACE "FExternalLibsModule"

void FExternalLibsModule::StartupModule()
{
}

void FExternalLibsModule::ShutdownModule()
{
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FExternalLibsModule, ExternalLibs)
