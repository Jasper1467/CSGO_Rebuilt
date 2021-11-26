#include "CBasePlayer.h"

CCommandContext* CBasePlayer::GetCommandContext(int nIndex)
{
	if (nIndex < 0 || nIndex >= m_CommandContext.Count())
		return 0;

	return &m_CommandContext[nIndex];
}

int CBasePlayer::DetermineSimulationTicks()
{
	int nSimulationTicks = 0;
	for (int i = 0; i < m_CommandContext.Count(); i++)
	{
		CCommandContext* pCtx = GetCommandContext(i);
		nSimulationTicks += pCtx->m_nNumCommands + pCtx->m_nDroppedPackets;
	}

	if (nSimulationTicks > v1 + 0x49B)
		nSimulationTicks = v1 + 0x49B;

	return nSimulationTicks;
}