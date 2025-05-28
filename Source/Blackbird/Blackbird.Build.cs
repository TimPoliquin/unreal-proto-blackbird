// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Blackbird : ModuleRules
{
	public Blackbird(ReadOnlyTargetRules Target) : base(Target)
	{
		this.PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		this.PublicDependencyModuleNames.AddRange(new[]
		{
			"Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "GameplayAbilities", "UMG",
			"ModelViewViewModel", "GameplayTasks"
		});

		this.PrivateDependencyModuleNames.AddRange(new[] { "GameplayTags", "Niagara" });

		this.PublicIncludePaths.Add("Blackbird/Public");
		this.PrivateIncludePaths.Add("Blackbird/Private");

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}