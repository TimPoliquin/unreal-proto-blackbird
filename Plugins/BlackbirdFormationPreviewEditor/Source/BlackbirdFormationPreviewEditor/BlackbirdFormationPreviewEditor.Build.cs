using UnrealBuildTool;

public class BlackbirdFormationPreviewEditor : ModuleRules
{
	public BlackbirdFormationPreviewEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicDependencyModuleNames.AddRange(
            new string[] { 
                "Core", 
                "CoreUObject", 
                "Engine", 
                "InputCore",
                "Blackbird"
            });

        PrivateDependencyModuleNames.AddRange(
            new string[] { 
                "UnrealEd", 
                "ComponentVisualizers" 
            });
	}
}