using UnrealBuildTool;
using System.Collections.Generic;

public class EtherroadServerTarget : TargetRules
{
    public EtherroadServerTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Server;
        DefaultBuildSettings = BuildSettingsVersion.V5;
        IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_7;
        ExtraModuleNames.Add("Etherroad");
    }
}
