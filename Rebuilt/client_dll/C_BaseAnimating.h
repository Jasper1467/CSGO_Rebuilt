#pragma once

#include "C_BasePlayer.h"
#include "../mixed/Studio.h"

class C_BaseAnimating : public C_BasePlayer
{
public:
	int LookupBone(const char* szName);
	void* GetModelPtr();
	bool ShouldSkipAnimationFrame();
	bool IsPlayer(); // 158

	void SetSequence(int nSequence); // 219

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

	void* m_pModelPtr; // this[2644]
	int m_nLastNonSkippedFrame; // this[666]

	int m_nComputedLODframe; // this + 0x28C
	float m_flCycle; // this + 0xA14
	float m_flPlaybackRate; // this + 0xA18

	static bool s_bEnableInvalidateBoneCache;
};

struct CBoneMergeCache
{
	C_BaseAnimating* m_pOwner;
	C_BaseAnimating* m_pFollow;
	CStudioHdr* m_pFollowHdr;
	const studiohdr_t* m_pFollowRenderHdr;
	CStudioHdr* m_pOwnerHdr;
	const studiohdr_t* m_pOwnerRenderHdr;
	int m_nCopiedFramecount;
	int m_nFollowBoneSetupMask;
	char pad1[640];
	bool m_bForceCacheClear;
};