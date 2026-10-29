using UnrealBuildTool;

public class EtherroadEditor : ModuleRules
{
    public EtherroadEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        PrivateDependencyModuleNames.AddRange(new[] { "Core", "CoreUObject", "Engine", "UnrealEd", "Etherroad" });
    }
}
