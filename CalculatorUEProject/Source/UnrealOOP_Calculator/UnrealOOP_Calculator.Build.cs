// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UnrealOOP_Calculator : ModuleRules
{
	public UnrealOOP_Calculator(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new[] { "Core", "CoreUObject", "Engine", "UMG" });

        // Defer resolution until first use
        PublicDelayLoadDLLs.Add("ArithmeticAPI.dll");
    }
}
