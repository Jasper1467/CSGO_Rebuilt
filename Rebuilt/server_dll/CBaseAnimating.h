#pragma once

struct __declspec(align(4)) CAnimationLayer
{
	int m_fFlags;
	bool m_bSequenceFinished;
	bool m_bLooping;
	char pad_0x0006[2];
	int m_nSequence;
	float m_flCycle;
	float m_flPlaybackRate;
	char pad_0x0014[4];
	float m_flWeight;
	float m_flWeightDeltaRate;
	char pad_0x001C[24];
	void* m_pDispatchedStudioHdr;
	Activity_t m_nDispatchedSrc;
	Activity_t m_nDispatchedDst;
	char pad_0x001C_2[8];
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

	CAnimationLayer* m_AnimOverlay[13]; // this[0x135]
};

class CBaseAnimating
{
public:

};