#pragma once

#include "CNetChan.h"

class CEngineClient
{
public:
	int GetMaxClients();
	bool IsInGame();
	bool IsConnected();
	const char* GetLevelName();
	const char* GetLevelNameShort();
	INetChannel* GetNetChannel();
	bool IsHLTV();
};

// Using as interface
inline CEngineClient* g_pEngineClient;