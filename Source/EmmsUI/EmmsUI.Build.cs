using System.IO;
using UnrealBuildTool;

namespace UnrealBuildTool.Rules
{
	public class EmmsUI : ModuleRules
	{
		public EmmsUI(ReadOnlyTargetRules Target) : base(Target)
		{
			PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

			PublicDependencyModuleNames.AddRange(new string[]
			{
				"Core",
				"CoreUObject",
				"Engine",
				"AngelscriptCode",
				"Slate",
				"SlateCore",
				"InputCore",
				"UMG",
                "DeveloperSettings"
			});

			if(Target.bCompileAgainstEditor)
			{
				PrivateDependencyModuleNames.AddRange(
					new string[]
					{
						"UnrealEd",
					});
			}
		}
	}
}
