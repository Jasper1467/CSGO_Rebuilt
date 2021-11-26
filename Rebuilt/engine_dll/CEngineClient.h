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
	INetChannelInfo* GetNetChannelInfo();
	bool IsHLTV();

	bool IsPlayingDemo(); // Index 82
	bool IsPaused(); // Index 90
	bool IsOccluded();
	int GetCurrentViewId();
	const char* GetGameDirectory();
};

// Using as interface
inline CEngineClient* g_pEngineClient;