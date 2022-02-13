// Copyright Epic Games, Inc. All Rights Reserved.

#include "lua.h"
#include "Core.h"
#include "Modules/ModuleManager.h"
#include "Interfaces/IPluginManager.h"

// Imports Lua headers
#include "ThirdParty/lua54/lua54.h"

#define LOCTEXT_NAMESPACE "FLuaModule"

void FLuaModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	// Get the base directory of this plugin
	FString BaseDir = IPluginManager::Get().FindPlugin("ExternalLibs")->GetBaseDir();

	// Add on the relative location of the third party dll and load it
	FString LibraryPath;

#if PLATFORM_WINDOWS
	LibraryPath = FPaths::Combine(*BaseDir, TEXT("Binaries/ThirdParty/lua54/Win64/lua54.dll"));
#endif // PLATFORM_WINDOWS

#if PLATFORM_ANDROID
	LibraryPath = FPaths::Combine(*BaseDir, TEXT("Binaries/ThirdParty/lua54/Win64/lua54.dll"));
#endif // PLATFORM_ANDROID

	LuaDLLHandle = !LibraryPath.IsEmpty() ? FPlatformProcess::GetDllHandle(*LibraryPath) : nullptr;

	if (LuaDLLHandle)
	{
		// Show dialog box if we successfully load the dll
		FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("Lua54", "Lua library loaded!"));

		if (lua_State* Lua = luaL_newstate())
		{
			FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("Lua54", "Lua library initialized!"));
		}
	}
	else
	{
		FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("ThirdPartyLibraryError", "Failed to load lua library"));
	}
}

void FLuaModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	// Free the dll handle
	FPlatformProcess::FreeDllHandle(LuaDLLHandle);
	LuaDLLHandle = nullptr;
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FLuaModule, lua)
