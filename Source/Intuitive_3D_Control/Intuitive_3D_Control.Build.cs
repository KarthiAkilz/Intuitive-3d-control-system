// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;


public class Intuitive_3D_Control : ModuleRules
{
    public Intuitive_3D_Control(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "WebSockets", "Json", "JsonUtilities" });

        PrivateDependencyModuleNames.AddRange(new string[] { });


    }
}
