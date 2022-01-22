#pragma once
#include "../mixed/SomeDefs.h"

#define MULTIPLAYER_BACKUP 150

class C_BaseEntity
{
public:
	int entindex();
	bool PredictionErrorShouldResetLatchedForAllPredictables() { return true; } // Index 133

	void* GetPredictedFrame(int nFrameNumber)
	{
		if (m_pOriginalData)
			return *(void**)m_pIntermediateData[nFrameNumber % MULTIPLAYER_BACKUP];

		return 0;
	}

	void _SUB_Remove()
	{
		if (m_iHealth > 0)
		{
			m_iHealth = 0;
			DevWarning(2, "SUB_Remove called on entity with health > 0\n");
		}

		Remove();
	}

	enum
	{
		SLOT_ORIGINALDATA = -1
	};

	int m_iHealth; // this + 0x100
	int m_nSurfaceType; // this + 0x280
	int m_nMoveType; // this + 0x25C
	unsigned char* m_pIntermediateData[MULTIPLAYER_BACKUP]; // this + 0x478
	unsigned char* m_pOriginalData; // this + 0x92C
	int m_nIntermediateData_FirstPredictedShiftMarker; // this + 0x934
	int m_nIntermediateDataCount; // this + 0x930
};