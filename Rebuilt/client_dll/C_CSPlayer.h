#pragma once

class CStudioHdr;
#include "C_BaseAnimating.h"

class C_CSPlayer : public C_BaseAnimating
{
public:
	void BuildTransformations(CStudioHdr* pHdr, int a3, int a4, int a5, int nBoneMask, int nBoneComputed);

	// [actual address in first opcode] E8 ? ? ? ? D9 45 08 5F
	float GetPoseParameter(int nIndex);

	int m_nPlayerState; // this + 0x9978
	bool m_bIsPlayerGhost; // this + 0x9ae1
	float m_flThirdpersonRecoil; // this + 0x467B
};