// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ManualBreathing : ModuleRules
{
	public ManualBreathing(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput", "UMG" });
	}
}
