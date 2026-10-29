using UnrealBuildTool;
using System.Collections.Generic;

public class EtherroadTarget : TargetRules
{
    public EtherroadTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Game;
        DefaultBuildSettings = BuildSettingsVersion.V5;
        IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_7;
        ExtraModuleNames.Add("Etherroad");
    }
}
