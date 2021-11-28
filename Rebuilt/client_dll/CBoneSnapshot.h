#pragma once
#include "../mixed/Vectors.h"
#include "../mixed/CUtlVector.h"
#include "../mixed/Studio.h"

class C_BaseAnimating;

class CBoneSnapshot
{
public:
	void Init()
	{
		// 56 8B F1 68 00 01 00 00

		m_pEntity = 0;
		m_flWeight = 0.0;
		memset(m_Weightlist, 0, MAXSTUDIOBONES);
		m_bWeightlistInitialized = 0;
		m_bCapturePending = 0;
		m_SubordinateSnapshots.RemoveAll();
		m_flDecayIdealDuration = 0.25;
		m_flDecayStartTime = 0.0;
		m_flDecayEndTime = 0.0;
		m_vecWorldCapturePos.x = 0.0;
		m_vecWorldCapturePos.y = 0.0;
		m_vecWorldCapturePos.z = 0.0;
		m_flLastBoneSetupTimeIndex = 0.0;
		m_nStudioRenderHdrId = -1;
	}

	void Update(C_BaseAnimating* pEnt, bool bReadOnly);

	bool IsCapturePending()
	{
		// 80 B9 15 34 00 00 00
		return m_bEnabled && m_bCapturePending;
	}

	C_BaseAnimating* m_pEntity;
	float m_flWeight;
	char pad[7];
	matrix3x4a_t m_Cache[MAXSTUDIOBONES];
	const char* m_szWeightlistName;
	float m_Weightlist[MAXSTUDIOBONES];
	bool m_bWeightlistInitialized;
	bool m_bEnabled;
	bool m_bCapturePending;
	float m_flDecayIdealDuration;
	float m_flDecayStartTime;
	float m_flDecayEndTime;
	Vector m_vecWorldCapturePos;
	float m_flLastBoneSetupTimeIndex;
	int m_nStudioRenderHdrId;
	CUtlVector<CBoneSnapshot*> m_SubordinateSnapshots;
};