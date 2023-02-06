// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Gilt : ModuleRules
{
	public Gilt(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {  
			"Core",
			"CoreUObject",
			"ApplicationCore",
			"Engine",
			"InputCore",
			"GameplayAbilities",
			"Niagara",
			"EnhancedInput",
			"StructUtils",
		});
		PrivateDependencyModuleNames.AddRange(new string[] {
			"Slate",
			"SlateCore",
			"AIModule",
			"AsyncMixin",
			"AudioMixer",
			"AudioModulation",
			"CommonUI",
			"CommonInput",
			"CommonLoadingScreen",
			"CommonGame",
			"GameFeatures",
			"GameplayMessageRuntime",
			"GameplayTags",
			"GameplayTasks",
			"ModularGameplay",
			"ModularGameplayActors",
			"NavigationSystem",
			"TargetingSystem",
			"UIExtension",
			"UMG"
		});
	}
}
