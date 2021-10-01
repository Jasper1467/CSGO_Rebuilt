#pragma once

class CGlobalVarsBase
{
public:
	// Used for encoding m_flSimulation and m_flAnimTime
	int GetNetworkBase(int nTick, int nEntity)
	{
		int nEntityMod = nEntity % m_nTimestampRandomizeWindow;
		int nBaseTick = m_nTimestampNetworkingBase * ((nTick - nEntityMod) / m_nTimestampNetworkingBase);
		return nBaseTick;
	}

	float m_flRealTime; // Absolute time per frame still - Use Plat_FloatTime()
	int m_nFrameCount; // Absolute frame counter, increases even if the game is paused
	float m_flAbsoluteFrameTime; // Non-paused m_flFrameTime
	float m_flAbsoluteFrameStartTimeStdDev;
	float m_flCurTime;
	float m_flFrameTime; // Time of spend on last server or client frame (has nothing todo with think intervals)
	int m_nMaxClients; // Current maxplayers setting
	int m_nTickCount; // Simulation ticks, does not increase when game is paused
	float m_flIntervalPerTick; // Simulation tick interval
	float m_flInterpolationAmount; // Interpolation amount (client-only) based on fraction of next tick has elapsed
	int m_nSimTicksThisFrame;
	int m_nNetworkProtocol;
	void* m_pSaveData; // Current savestore data
	bool m_bClient; // Set to true in client code
	bool m_bRemoteClient;
	int m_nTimestampNetworkingBase;
	int m_nTimestampRandomizeWindow;
};

struct CGlobalVars : CGlobalVarsBase
{
	const char* m_szMapName;
	const char* m_szMapGroupName;
	int m_nMapVersion;
	const char* m_szStartSpot;
	int m_nLoadingType; // How the current map was loaded
	bool m_bMapUpdateFailed; // Map has failed to load, we need to kick back to the main menu
	bool m_bDeathMatch;
	bool m_bCooperative;
	bool m_bTeamPlay;
	int m_nMaxEntities; // Current max entities
	int m_nServerCount;
	void* m_pEdicts;
};

// Usesing these as interfaces
CGlobalVarsBase* g_pGlobals;
CGlobalVars* g_pServerGlobals;