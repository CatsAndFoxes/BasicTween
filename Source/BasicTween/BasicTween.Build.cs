using UnrealBuildTool;

public class BasicTween : ModuleRules
{
	public BasicTween(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(new string[] {});
		PrivateIncludePaths.AddRange(new string[] {});
		
		PublicDependencyModuleNames.AddRange(new string[]{"Core", "Engine"});
		PrivateDependencyModuleNames.AddRange(new string[]{"CoreUObject", "Slate", "SlateCore"});
		DynamicallyLoadedModuleNames.AddRange(new string[]{});
	}
}
