// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class AndroidGame : ModuleRules
{
	public AndroidGame(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {"Core", "CoreUObject", "Engine", "InputCore", "ImageWrapper"});

		// Plugins dependencies
		PublicDependencyModuleNames.AddRange(new string[] {"ExternalLibs", "PhotoLibrary"});
	}
}
