#include "CCSGOPlayerAnimState.h"

#include "../mixed/CGlobalVarsBase.h"

float CycleClamp(float flCycle)
{
	float flTemp = flCycle;

	if (flTemp < 0.0f)
		flTemp += 1.0f;
	else
		flTemp -= 1.0f;

	return flTemp;
}


void CCSGOPlayerAnimState::IncrementLayerCycle(int nLayer, bool a3)
{
	CAnimationLayer* pLayer = (CAnimationLayer*)(*((uintptr_t*)m_pPlayer + 0x135) + 92 * nLayer);

	if (!pLayer || fabs(pLayer->m_flPlaybackRate) <= 0.0f)
		return;

	float v7 = m_flLastUpdateIncrement * pLayer->m_flPlaybackRate + pLayer->m_flCycle;
	if (!a3 && v7 >= 1.0f)
		v7 = 0.999f;

	pLayer->m_flCycle = CycleClamp(v7);
}