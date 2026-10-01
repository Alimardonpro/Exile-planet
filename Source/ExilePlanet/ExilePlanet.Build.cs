// Copyright Exile Planet. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

public class ExilePlanet : ModuleRules
{
	public ExilePlanet(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"UMG",
			"Slate",
			"SlateCore"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			ModuleDirectory,
			Path.Combine(ModuleDirectory, "Core"),
			Path.Combine(ModuleDirectory, "Player"),
			Path.Combine(ModuleDirectory, "Vehicle"),
			Path.Combine(ModuleDirectory, "Mission"),
			Path.Combine(ModuleDirectory, "World"),
			Path.Combine(ModuleDirectory, "Intro"),
			Path.Combine(ModuleDirectory, "UI"),
			Path.Combine(ModuleDirectory, "Online")
		});
	}
}
