using UnrealBuildTool;

public class ERCore : ModuleRules
{
    public ERCore(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        PublicDependencyModuleNames.AddRange(new[] { "Core", "CoreUObject", "Engine", "NetCore", "GameplayTags" });
    }
}
