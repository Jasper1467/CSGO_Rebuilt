#pragma once

class CStudioHdr;
#include "C_BasePlayer.h"

class C_CSPlayer : public C_BasePlayer
{
public:
	void BuildTransformations(CStudioHdr* pHdr, int a3, int a4, int a5, int nBoneMask, int m_nBoneComputed);

	int m_nPlayerState; // this + 0x9978
};