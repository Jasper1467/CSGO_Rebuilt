#include "CCSPlayerAnimState.h"
#include "CCSGameStats.h"

ConVar post_jump_crouch;

bool CCSPlayerAnimState::HandleJumping()
{
	if (!m_bJumping)
		return m_bJumping; // Lmao, valve...

	if (m_bJumpThisFrame)
	{
		g_GameStats.IncrementStat(m_pPlayer, 193, 1, 0, 0);

		m_bJumpThisFrame = false;
		RestartMainSequence();
	}

	if ((g_pServerGlobals->m_flCurTime - m_flJumpStartTime) <= 0.2f || !(m_pOuter->m_fFlags) & FL_ONGROUND)
		return m_bJumping;

	m_flPostLandCrouchEndTime = g_pServerGlobals->m_flCurTime + post_jump_crouch.GetFloat();
	return m_bJumping;
}