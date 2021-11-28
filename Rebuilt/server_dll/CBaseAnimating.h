#pragma once
#include "../mixed/Studio.h"
#include "../mixed/CGlobalVarsBase.h"
#include "CBaseEntity.h"
#include "../mixed/CUtlVector.h"

class __declspec(align(4)) CAnimationLayer
{
public:

	void SetCycle(float flCycle)
	{
		if (m_pOwner && m_flCycle != flCycle)
			m_pOwner->InvalidatePhysicsRecursive(ANIMATION_CHANGED);

		m_flCycle = flCycle;
	}

	int m_fFlags;
	bool m_bSequenceFinished;
	bool m_bLooping;
	char pad_0x0006[2];
	int m_nSequence;
	float m_flCycle;
	float m_flPlaybackRate;
	float m_flPrevCycle;
	float m_flWeight;
	float m_flWeightDeltaRate;
	float m_flBlendIn;
	float m_flBlendOut;
	float m_flKillRate;
	float m_flKillDelay;
	float m_flLayerAnimTime;
	float m_flLayerFadeOuttime;
	void* m_pDispatchedStudioHdr;
	Activity_t m_nDispatchedSrc;
	Activity_t m_nDispatchedDst;
	Activity_t m_nActivity;
	int m_nPriority;
	int m_nOrder;
	float m_flLastEventCheck;
	float m_flLastAccess;
	CBaseEntity* m_pOwner;
};


class CBaseAnimating
{
public:
	void SetCycle(float flCycle)
	{
		m_flCycle = flCycle;
	}

	float m_flAnimTime; // this + 0x68
	char pad[149];
	float m_flCycle; // this + 0xFD
	char pad1[107];
	int m_fFlags; // this + 0x360
	char pad2[3045];
};

class CBaseAnimatingOverlay : public CBaseAnimating
{
public:
	void SetNumAnimOverlays(int nNum);
	int GetNumAnimOverlays();

	CUtlVector<CAnimationLayer> m_AnimOverlay; // this + 0x4D4
};