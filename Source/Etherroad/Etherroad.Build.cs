using UnrealBuildTool;

public class Etherroad : ModuleRules
{
    public Etherroad(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        PublicDependencyModuleNames.AddRange(new[]
        {
            "Core", "CoreUObject", "Engine", "InputCore",
            "EnhancedInput", "NetCore", "GameplayTags",
            "GameplayTasks", "AIModule", "EtherroadCore"
        });
        PrivateDependencyModuleNames.AddRange(new[] { "UMG", "Slate", "SlateCore" });
    }
}
