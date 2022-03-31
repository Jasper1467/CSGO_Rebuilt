#pragma once
#include "../mixed/SomeDefs.h"

#define MULTIPLAYER_BACKUP 150

struct VarMapEntry_t
{
	unsigned __int16 m_nType;
	unsigned __int16 m_bNeedsToInterpolate;
	void* m_pData;
	void* m_pWatcher;
};

struct VarMapping_t
{
	VarMapping_t()
	{
		m_nInterpolatedEntries = 0;
	}

	CUtlVector<VarMapEntry_t> m_Entries;
	int m_nInterpolatedEntries;
	float m_flLastInterpolationTime;
};

class C_BaseEntity
{
public:
	Vector GetAbsOrigin(); // 10

	int entindex();
	void SetAbsAngles(QAngle angAngles);
	void InvalidatePhysicsRecursive(int nBits);

	bool PredictionErrorShouldResetLatchedForAllPredictables() { return true; } // 133

	void* GetPredictedFrame(int nFrameNumber)
	{
		if (m_pOriginalData)
			return *(void**)m_pIntermediateData[nFrameNumber % MULTIPLAYER_BACKUP];

		return 0;
	}

	void SUB_Remove()
	{
		if (m_iHealth > 0)
		{
			m_iHealth = 0;
			DevWarning(2, "SUB_Remove called on entity with health > 0\n");
		}

		Remove();
	}

	VarMapping_t* GetVarMapping()
	{
		return &m_VarMap;
	}

	enum
	{
		SLOT_ORIGINALDATA = -1
	};

	VarMapping_t m_VarMap; // this + 0x9

	int m_iHealth; // this + 0x100
	int m_nSurfaceType; // this + 0x280
	int m_nMoveType; // this + 0x25C
	unsigned char* m_pIntermediateData[MULTIPLAYER_BACKUP]; // this + 0x478
	unsigned char* m_pOriginalData; // this + 0x92C
	int m_nIntermediateData_FirstPredictedShiftMarker; // this + 0x934
	int m_nIntermediateDataCount; // this + 0x930

	Vector m_vecOrigin; // this + 0xac
};