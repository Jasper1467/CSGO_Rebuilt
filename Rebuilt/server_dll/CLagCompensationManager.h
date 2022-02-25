#pragma once
#include "../mixed/Vectors.h"
#include "CBasePlayer.h"

#define LAGCOMP_FRACTION_SCALE 0.95f
#define LAGCOMP_TELEPORTED_DISTANCE_SQR (64.0f * 64.0f)

struct LayerRecord
{
	int m_nSequence;
	float m_flCycle;
	float m_flWeight;
	int m_nOrder;
};


struct LagRecord
{
	int m_fFlags;
	Vector m_vecOrigin;
	QAngle m_angAngles;
	Vector m_vecMins;
	Vector m_vecMaxs;
	float m_flSimulationTime;
	LayerRecord m_LayerRecords[15];
	int m_nMasterSequence;
	float m_flMasterCycle;
	float m_flPoseParameters[24];
};

enum LagCompensationState_t
{
	LC_NO = 0x0,
	LC_ALIVE = 0x1,
	LC_ORIGIN_CHANGED = 0x100,
	LC_ANGLES_CHANGED = 0x200,
	LC_SIZE_CHANGED = 0x400,
	LC_ANIMATION_CHANGED = 0x800,
};

class CLagCompensationManager
{
public:
	char pad[32];
	bool m_bNeedToRestore;
	CBasePlayer* m_pCurrentPlayer;
	int m_nLagCompensationType;
	Vector m_vecWeaponPos;
	QAngle m_angWeaponAngles;
	float m_flWeaponRange;
	bool m_bIsCurrentlyDoingCompensation;
};