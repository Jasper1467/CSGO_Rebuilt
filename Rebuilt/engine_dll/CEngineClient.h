#pragma once

#include "CNetChan.h"

struct player_info_t
{
	__int64 m_nVersion;
	union
	{
		__int64 m_nSteamID64;
		struct
		{
			__int32 m_nXUIDlow;
			__int32 m_nXUIDhigh;
		};
	};
	char m_szName[128];
	int m_nUserId;
	char m_szGuid[20];
	char pad_0x00A8[16];
	unsigned int m_nSteamID;
	char m_szFriendsName[128];
	bool m_bFakePlayer;
	bool m_bIsHltv;
	unsigned int m_nCustomFiles[4];
	unsigned __int8 m_FilesDownloaded;
};

bool g_bDedicatedServer;
char g_szComGameDir[260];

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
	void* GetAchievementMgr();
	float GetLastTimeStamp();
};

// Using as interface
inline CEngineClient* g_pEngineClient;