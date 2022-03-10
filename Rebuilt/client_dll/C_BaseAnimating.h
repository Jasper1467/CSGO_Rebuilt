#pragma once

#include "C_BasePlayer.h"
#include "../mixed/Studio.h"
#include "../mixed/CMemAlloc.h"

class C_BaseAnimating : public C_BasePlayer
{
public:
	int LookupBone(const char* szName);
	CStudioHdr* GetModelPtr();
	bool ShouldSkipAnimationFrame();
	bool IsPlayer(); // 158

	void SetSequence(int nSequence); // 219

	//55 8B EC 57 8B 7D 08 85 FF 75 08
	int LookupPoseParameter(CStudioHdr* pHdr, const char* szName);

	void SetPlaybackRate(float flPlaybackRate) { m_flPlaybackRate = flPlaybackRate; }
	void SetCycle(float flCycle)
	{
		if (m_flCycle != flCycle)
		{
			m_flCycle = flCycle;
			InvalidatePhysicsRecursive(ANIMATION_CHANGED);
		}
	}

	static void EnableInvalidateBoneCache(bool bEnable) { s_bEnableInvalidateBoneCache = bEnable; }

	C_AnimationLayer* GetAnimOverlay(int i, bool bUseOrder);

	CStudioHdr* m_pModelPtr; // this[2644]
	int m_nLastNonSkippedFrame; // this[666]

	int m_nComputedLODframe; // this + 0x28C
	float m_flCycle; // this + 0xA14
	float m_flPlaybackRate; // this + 0xA18

	static bool s_bEnableInvalidateBoneCache;
};

class CBoneMergeCache
{
public:
	CBoneMergeCache()
	{
		Init(0);
	}

	void Init(C_BaseAnimating* pOwner)
	{
		m_pOwner = pOwner;
		m_pFollow = 0;
		m_pFollowHdr = 0;
		m_pOwnerHdr = 0;
		m_pFollowRenderHdr = 0;
		m_nFollowBoneSetupMask = 0;
		m_bForceCacheClear = 0;
		*(int*)pad1[108] = 0;

		if (pad1[104] >= 0)
		{
			if (pad1[96])
			{
				g_pMemAlloc->Alloc(*(int*)pad1[96]);
				*(int*)pad1[96] = 0;
			}
			*(int*)pad1[100] = 0;
		}

		*(int*)pad1[112] = *(int*)pad1[96];

		memset(m_nRawIndexMapping, 255, sizeof(m_nRawIndexMapping));
	}

	C_BaseAnimating* m_pOwner;
	C_BaseAnimating* m_pFollow;
	CStudioHdr* m_pFollowHdr;
	const studiohdr_t* m_pFollowRenderHdr;
	CStudioHdr* m_pOwnerHdr;
	const studiohdr_t* m_pOwnerRenderHdr;
	int m_nCopiedFramecount;
	int m_nFollowBoneSetupMask;
	char pad1[128];
	unsigned short m_nRawIndexMapping[MAXSTUDIOBONES];
	bool m_bForceCacheClear;
};