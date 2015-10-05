// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class Godzilla : ModuleRules
{

	private string ModulePath
	{
		get { return Path.GetDirectoryName(RulesCompiler.GetModuleFilename(this.GetType().Name)); }
	}

	private string ThirdPartyPath
	{
		get { return Path.GetFullPath(Path.Combine(ModulePath, "../../ThirdParty/")); }
	}

	public Godzilla(TargetInfo Target)
	{
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		LoadVRPN(Target);
		LoadQuat(Target);
	}

	public bool LoadVRPN(TargetInfo Target)
	{
		bool isLibrarySupported = false;

		if ((Target.Platform == UnrealTargetPlatform.Win64) || (Target.Platform == UnrealTargetPlatform.Win32))
		{
			isLibrarySupported = true;

			string PlatformString = (Target.Platform == UnrealTargetPlatform.Win64) ? "x64" : "x86";
			string LibrariesPath = Path.Combine(ThirdPartyPath, "vrpn", "lib");

			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "vrpn." + PlatformString + ".lib"));
		}

		if (isLibrarySupported)
		{
			// Include path
			PublicIncludePaths.Add(Path.Combine(ThirdPartyPath, "vrpn", "include"));
		}

		Definitions.Add(string.Format("WITH_VRPN_BINDING={0}", isLibrarySupported ? 1 : 0));

		return isLibrarySupported;
	}

	public bool LoadQuat(TargetInfo Target)
	{
		bool isLibrarySupported = false;

		if ((Target.Platform == UnrealTargetPlatform.Win64) || (Target.Platform == UnrealTargetPlatform.Win32))
		{
			isLibrarySupported = true;

			string PlatformString = (Target.Platform == UnrealTargetPlatform.Win64) ? "x64" : "x86";
			string LibrariesPath = Path.Combine(ThirdPartyPath, "vrpn", "lib");

			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "quat." + PlatformString + ".lib"));
		}

		if (isLibrarySupported)
		{
			// Include path
			PublicIncludePaths.Add(Path.Combine(ThirdPartyPath, "vrpn", "include"));
		}

		Definitions.Add(string.Format("WITH_QUAT_BINDING={0}", isLibrarySupported ? 1 : 0));

		return isLibrarySupported;
	}
}
