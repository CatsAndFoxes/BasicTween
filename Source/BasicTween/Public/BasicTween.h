#pragma once

#include "Modules/ModuleManager.h"
#include "Tickable.h"

class FBasicTweenModule : public IModuleInterface {
public:
	// IModuleInterface interface
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
