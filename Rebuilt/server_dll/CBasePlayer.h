#pragma once

#include "../mixed/CUtlVector.h"
#include "CUserCmd.h"
#include "../engine_dll/ConVar.h"

struct CPlayerSimInfo
{
	float m_flTime;
	int m_nNumCommands;
	int m_nTicksCorrected;
	float m_flFinalSimulationTime;
	float m_flGameSimulationTime;
	float m_flServerFrameTime;
	Vector m_vecAbsOrigin;
};

struct CCommandContext
{
	CUtlVector<CUserCmd> m_Commands;
	int m_nNumCommands;
	int m_nTotalCommands;
	int m_nDroppedPackets;
	bool m_bPaused;
};

class CBasePlayer
{
public:
	CCommandContext* GetCommandContext(int nIndex);
	int DetermineSimulationTicks();

	CUtlVector<CCommandContext> m_CommandContext; // this + 0x37B

	int m_fFlags; // this + 0x36
	Vector m_vecAbsOrigin; // this + 0x77
	int m_iHealth; // this + 0x8C
	int m_nWaterLevel; // this + 0x163
	float m_flMaxSpeed; // this + 0x41A
	int m_nBodyPitchPoseParam; // this + 0x47B
	int m_nWaterType; // this +  0x118
	QAngle m_viewPunchAngle; // this + 0xA4C
	bool m_bIsUnderwater; // this + 0x10F8
};