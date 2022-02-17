// Copyright Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class PhotoLibrary : ModuleRules
{
	public PhotoLibrary(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.AddRange(
			new string[]
			{
				// ... add public include paths required here ...
			}
		);


		PrivateIncludePaths.AddRange(
			new string[]
			{
				// ... add other private include paths required here ...
			}
		);


		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				// ... add other public dependencies that you statically link with here ...
			}
		);


		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine"
				// ... add private dependencies that you statically link with here ...	
			}
		);


		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
		);

		// Plugin setup for Android
		if (Target.Platform == UnrealTargetPlatform.Android)
		{
			PrivateDependencyModuleNames.AddRange(new string[] {"Launch", "ApplicationCore"});

			PrivateIncludePaths.AddRange(new string[] {"/Source/Runtime/Launch/Private"});

			string pluginPath = Utils.MakePathRelativeTo(ModuleDirectory, Target.RelativeEnginePath);
			
			// !!! Deprecated !!!
			//AdditionalPropertiesForReceipt.Add(new ReceiptProperty("PhotoLibrary", Path.Combine(pluginPath, "PhotoLibrary_APL.xml")));
			
			// !!! New method !!!
			AdditionalPropertiesForReceipt.Add("PhotoLibrary", Path.Combine(pluginPath, "PhotoLibrary_APL.xml"));
		}
	}
}
