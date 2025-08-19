#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class EMMSUI_API FEmmsUIModule : public FDefaultModuleImpl
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};