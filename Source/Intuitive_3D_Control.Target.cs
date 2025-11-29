// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class Intuitive_3D_ControlTarget : TargetRules
{
    public Intuitive_3D_ControlTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Game;
        DefaultBuildSettings = BuildSettingsVersion.V5;
        IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_6;
        ExtraModuleNames.AddRange(new string[] { "Intuitive_3D_Control" });
    }
}
