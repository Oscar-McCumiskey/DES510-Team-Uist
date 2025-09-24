// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class DES510_Team_Uist : ModuleRules
{
	public DES510_Team_Uist(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"DES510_Team_Uist",
			"DES510_Team_Uist/Variant_Platforming",
			"DES510_Team_Uist/Variant_Combat",
			"DES510_Team_Uist/Variant_Combat/AI",
			"DES510_Team_Uist/Variant_SideScrolling",
			"DES510_Team_Uist/Variant_SideScrolling/Gameplay",
			"DES510_Team_Uist/Variant_SideScrolling/AI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
