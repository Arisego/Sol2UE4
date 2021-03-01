// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
using UnrealBuildTool;
using System;
using System.IO;
using System.Collections.Generic;

public class Sol2Ue : ModuleRules
{
	public Sol2Ue(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				"Sol2Ue/Private",
                "ThirdParty/Sol2",
                "ThirdParty/Lua/include"
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				// ... add private dependencies that you statically link with here ...	
                "CoreUObject",
                "Engine",
            }
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);

		var ThirdPartyPath = Path.GetFullPath(Path.Combine(ModuleDirectory, "../ThirdParty/"));

        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            var LuaLibDir = ThirdPartyPath + "Lua/lib/x64/Lua5.3.lib";
            PublicAdditionalLibraries.Add(LuaLibDir);
        }
    }
}
