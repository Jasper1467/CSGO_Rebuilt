#pragma once
#include "../mixed/Studio.h"

struct __declspec(align(4)) CAnimationLayer
{
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
	float m_flLayerAnimtime;
	float m_flLayerFadeOuttime;
	void* m_pDispatchedStudioHdr;
	Activity_t m_nDispatchedSrc;
	Activity_t m_nDispatchedDst;
	Activity_t m_nActivity;
	int m_nPriority;
	int m_nOrder;
	float m_flLastEventCheck;
	float m_flLastAccess;
	void* m_pOwnerEntity;
};

class CBaseAnimatingOverlay
{
public:
	void SetNumAnimOverlays(int nNum);
	int GetNumAnimOverlays();

	CAnimationLayer* m_AnimOverlay[13]; // this + 0x4D4
};

class CBaseAnimating
{
public:

};