#pragma once

#include "../mixed/Vectors.h"
#include "CNetChan.h"

enum SingonState_t
{
	SIGNONSTATE_NONE = 0x0,
	SIGNONSTATE_CHALLENGE = 0x1,
	SIGNONSTATE_CONNECTED = 0x2,
	SIGNONSTATE_NEW = 0x3,
	SIGNONSTATE_PRESPAWN = 0x4,
	SIGNONSTATE_SPAWN = 0x5,
	SIGNONSTATE_FULL = 0x6,
	SIGNONSTATE_CHANGELEVEL = 0x7,
};

struct CClockDriftMgr
{
	float m_ClockOffsets[16];
	uint32_t m_nCurClockOffset;
	uint32_t m_nServerTick;
	uint32_t m_nClientTick;
};

class CBaseClientState
{
public:
	char pad000[156];
	INetChannel* m_pNetChannel;
	int m_nChallengeNr;
	char pad001[4];
	double m_dbConnectTime;
	int m_nRetryNumber;
	char pad002[84];
	int m_nSignonState;
	char pad003[4];
	double m_flNextCmdTime;
	int m_nServerCount;
	int m_nCurrentSequence;
	char pad004[8];
	CClockDriftMgr m_ClockDriftMgr;
	int m_nDeltaTick;
	char pad005[4];
	int m_nViewEntity;
	int m_nPlayerSlot;
	bool m_bPaused;
	char pad006[3];
	char m_szLevelName[260];
	char m_szLevelNameShort[40];
	char pad007[212];
	int m_nMaxClients;
	char pad008[18836];
};

class CClientState : public CBaseClientState
{
public:
	int m_nOldTickCount;
	float m_flTickRemainder;
	float m_flFrameTime;
	int m_nLastOutgoingCommand;
	int m_nChokedCommands;
	int m_nLastCommandAck;
	int m_nLastServerTick;
	int m_nCommandAck;
	int m_nSoundSequence;
	int m_nLastProgressPercent;
	bool m_bIsHltv;
	char pad009[75];
	QAngle m_angViewAngles;
	char pad010[204];
	void* m_pEvents;
};

// As interface
inline CClientState* g_pClientState;