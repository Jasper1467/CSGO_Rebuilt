#pragma once
#include "../engine_dll/CEngineVGui.h"

class IAppSystem
{
public:
	bool Connect(CreateInterfaceFn fnFactory);
	void Disconnect();
	void* QueryInterface(const char* szInterfaceName);
	int Init();
	void Shutdown();
	void* GetDependencies() { return 0; }
	int GetTier();
	void Reconnect(CreateInterfaceFn fnFactory, const char* szInterfaceName);
	bool IsSingleton() { return true; }
};