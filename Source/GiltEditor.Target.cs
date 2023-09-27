// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GiltEditorTarget : TargetRules
{
	public GiltEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		ExtraModuleNames.Add("Gilt");
	}
}
