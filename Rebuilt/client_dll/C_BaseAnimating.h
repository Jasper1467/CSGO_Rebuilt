#pragma once

#include "C_BaseEntity.h"
#include "../mixed/Studio.h"

class C_BaseAnimating : public C_BaseEntity
{
public:
	int LookupBone(const char* szName);
	void* GetModelPtr();
	bool ShouldSkipAnimationFrame();
	bool IsPlayer(); // 158

	void* m_pModelPtr; // this[2644]
	int m_nLastNonSkippedFrame; // this[666]
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