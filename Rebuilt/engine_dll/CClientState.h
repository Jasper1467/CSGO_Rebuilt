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

class ClientClass;

class CEventInfo
{
public:
	__int16 m_nClassId;
	float m_flFireDelay;
	const void* m_pSendTable;
	const ClientClass* m_pClientClass;
	int m_nBits;
	unsigned __int8* m_pData;
	int m_nFlags;
	char pad[24];
	CEventInfo* m_pNextEvent;
};

class CClockDriftMgr
{
public:
	float m_ClockOffsets[16];
	uint32_t m_nCurClockOffset;
	uint32_t m_nServerTick;
	uint32_t m_nClientTick;
};

class CBaseClientState
{
public:
	char pad_0000[156];
	INetChannel* m_pNetChannel;
	int m_nChallengeNr;
	char pad_00A4[100];
	int m_nSignonState;
	double m_dbNextCmdTime;
	int m_nServerCount;
	int m_nCurrentSequence;
	int musor_pads[2];
	CClockDriftMgr m_ClockDriftMgr;
	int m_nDeltaTick;
	char paused_align[4];
	int m_nViewEntity;
	int m_nPlayerSlot;
	bool m_bPaused;
	char bruh[3];
	char m_szLevelName[260];
	char m_szLevelNameShort[80];
	char m_szGroupName[80];
	char pad_032[92];
	int m_nMaxClients;
	char pad_0314[18828];
	float m_nLastServerTickTime;
	bool m_bInSimulation;
	char pad_4C9D[3];
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
	CEventInfo* m_pEvents;
};

// As interface
inline CClientState* g_pClientState;