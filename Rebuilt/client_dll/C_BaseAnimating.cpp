#include "C_BaseAnimating.h"
#include "../mixed/StringStuff.h"

#include <assert.h>
#include <math.h>
#include "../mixed/CGlobalVarsBase.h"

int C_BaseAnimating::LookupBone(const char* szName)
{
	// E8 ? ? ? ? 89 86 08 2A 00 00

	Assert(GetModelPtr());

	if (!GetModelPtr())
		return -1;

	int v4 = Studio_BoneIndexByName(GetModelPtr(), szName);
	if (v4 == -1)
	{
		if (V_stristr(szName, "weapon_bone"))
			v4 = Studio_BoneIndexByName(GetModelPtr(), "hand_R");
		else if (V_stristr(szName, "Bip01_Head"))
			v4 = Studio_BoneIndexByName(GetModelPtr(), "head_0");
		else if (V_stristr(szName, "L_Hand"))
			v4 = Studio_BoneIndexByName(GetModelPtr(), "hand_L");
		else if (V_stristr(szName, "R_Hand"))
			v4 = Studio_BoneIndexByName(GetModelPtr(), "hand_R");
	}

	return v4;
}

CStudioHdr* C_BaseAnimating::GetModelPtr()
{
	// E8 ? ? ? ? 8B F0 85 F6 74 06

	CStudioHdr* result; // eax

	if (!m_pModelPtr && (*(int(__thiscall**)(void*))(this[1] + 32))(this + 1))
		sub_101C87E0();

	result = m_pModelPtr;
	if (!result || !*result)
		result = 0;
	return result;
}

#define FPS_TO_FRAMETIME_SECS( _n ) (1000.0f / _n) * 0.001f

bool C_BaseAnimating::ShouldSkipAnimationFrame()
{
	// E8 ? ? ? ? 88 44 24 0B

	if (!IsPlayer())
		return false;

	int nFrameCount = g_pGlobals->m_nFrameCount;
	float flFrameTime = g_pGlobals->m_flFrameTime;

	if (!m_nLastNonSkippedFrame || abs(nFrameCount - m_nLastNonSkippedFrame) >= 2)
		return false;

	if (flFrameTime < FPS_TO_FRAMETIME_SECS(300.f)) // 0.0033f
	{
		if ((entindex() % 3 + nFrameCount) % 3)
			return true;
	}
	else if (flFrameTime < FPS_TO_FRAMETIME_SECS(200.f)) // 0.005f
	{
		if ((entindex() % 2 + nFrameCount) & 1)
			return true;
	}
	else if (flFrameTime < FPS_TO_FRAMETIME_SECS(150.f)) // 0.066f
	{
		if ((entindex() % 3 + nFrameCount) % 3)
			return true;
	}

	return false;
}