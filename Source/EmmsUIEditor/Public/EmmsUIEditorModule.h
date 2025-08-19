#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "Framework/Docking/WorkspaceItem.h"

class EMMSUIEDITOR_API FEmmsUIEditorModule : public FDefaultModuleImpl
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	void UpdatePostCompile();

	TMap<FName, UClass*> RegisteredNomadTabSpawners;
	TMap<FString, TSharedPtr<FWorkspaceItem>> ToolsMenuCategories;
	TMap<FName, UClass*> RegisteredClassDetailCustomizations;
	TMap<FName, UClass*> RegisteredScriptStructDetailCustomizations;
};