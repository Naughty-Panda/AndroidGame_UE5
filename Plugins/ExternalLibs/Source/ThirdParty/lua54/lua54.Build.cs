// Fill out your copyright notice in the Description page of Project Settings.

using System.IO;
using UnrealBuildTool;

public class lua54 : ModuleRules
{
	public lua54(ReadOnlyTargetRules Target) : base(Target)
	{
		Type = ModuleType.External;

		PublicDefinitions.Add("LUA_BUILD_AS_DLL");

		if (Target.Platform == UnrealTargetPlatform.Win64)
		{
			// Add the import library
			PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "lib", "liblua54.a"));

			// Delay-load the DLL, so we can load it from the right place first
			PublicDelayLoadDLLs.Add("lua54.dll");

			// Copy dll to target output
			RuntimeDependencies.Add("$(TargetOutputDir)/lua54.dll",
				Path.Combine(PluginDirectory, "Source/ThirdParty/lua54/lib/lua54.dll"));

			// Ensure that the DLL is staged along with the executable
			RuntimeDependencies.Add("$(PluginDir)/Binaries/ThirdParty/lua54/Win64/lua54.dll");
		}
		else if (Target.Platform == UnrealTargetPlatform.Android)
		{
			// Work in progress...
		}
	}
}
