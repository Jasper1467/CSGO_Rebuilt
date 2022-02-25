#include "CCSGOPlayerAnimState.h"

#include "../mixed/CGlobalVarsBase.h"

#include <algorithm>

void CCSGOPlayerAnimState::Update(QAngle& angView)
{
	if (m_pPlayer && m_pPlayer->IsAlive() && m_pPlayer->m_bIsPlayerGhost && CacheSequences())
	{
		angView.x = AngleNormalize(angView.x + m_pPlayer->m_flThirdpersonRecoil);

		if (m_flLastUpdateTime != g_pGlobals->m_flCurTime && m_nLastUpdateFrame != g_pGlobals->m_nFrameCount)
		{
			m_flLastUpdateIncrement = fmaxf(g_pGlobals->m_flCurTime - m_flLastUpdateTime, 0.0);

			m_pPlayer->EnableInvalidateBoneCache(false);

			m_flEyePitch = AngleNormalize(angView.x);
			m_flEyeYaw = AngleNormalize(angView.y);

			m_pPlayer->m_vecOrigin = m_pPlayer->GetAbsOrigin();

			m_pActiveWeapon = m_pPlayer->GetActiveWeapon();
			if (m_pActiveWeapon != m_pLastActiveWeapon || m_bFirstRunSinceInit)
			{
				m_pPlayer->m_nComputedLODframe = 0;

				for (int i = 0; i < LAYER_COUNT; i++)
				{
					C_AnimationLayer* pLayer = m_pPlayer->GetAnimOverlay(i, false);
					if (pLayer)
					{
						pLayer->m_pDispatchedStudioHdr = 0;
						pLayer->m_nDispatchedSrc = ACT_INVALID;
						pLayer->m_nDispatchedDst = ACT_INVALID;
					}
				}

				float v22;
				if (!IsPreCrouchUpdateDemo())
				{
					float v24;
					float v21;

					float v23 = m_pPlayer->m_flDuckAmount + m_flDuckAdditional;
					if (v23 >= 0.0)
						v24 = fminf(v23, 1.0);
					else
						v24 = 0.0;
					float v25 = m_flDuckAmount;
					float v26 = m_flLastUpdateIncrement * ANIM_DUCK_APPROACH_SPEED_DOWN;
					if ((v24 - v25) <= v26)
					{
						if (-v26 <= (v24 - v25))
							v21 = v24;
						else
							v21 = v25 - v26;
					}
					else
						v21 = v25 + v26;

					if (v21 < 0.0)
						v22 = 0.0;
				}
				else
				{
					float v21;
					float v17;
					float v18;
					float v19;

					if (m_pPlayer->m_fFlags & FL_ANIMDUCKING)
						v17 = 1.0;
					else
						v17 = m_flDuckAdditional;
					v18 = m_flDuckAmount;
					if (v17 <= v18)
						v19 = ANIM_DUCK_APPROACH_SPEED_DOWN;
					else
						v19 = ANIM_DUCK_APPROACH_SPEED_UP;

					float v20 = m_flLastUpdateIncrement * v19;
					if ((v17 - v18) <= v20)
					{
						if (-v20 <= (v17 - v18))
							v21 = v17;
						else
							v21 = v18 - v20;
					}
					else
						v21 = v18 + v20;

					m_flDuckAmount = v21;
					if (v21 < 0.0)
						v22 = 0.0;
				}

				m_flDuckAmount = v22;

				(*(void(__thiscall**)(int))(*(_DWORD*)g_pMdlCache + 132))(g_pMdlCache); // BeginLock

				m_pPlayer->SetSequence(0);
				m_pPlayer->SetPlaybackRate(0.f);
				m_pPlayer->SetCycle(0.f);

				(*(void(__thiscall**)(int))(*(_DWORD*)g_pMdlCache + 136))(v27); // EndLock

				SetupVelocity();
				SetupAimMatrix();
				SetupWeaponAction();
				SetupMovement();
				SetupAliveloop();
				SetupWholeBodyAction();
				SetUpFlashedReaction();
				SetupFlinch();
				SetupLean();

				for (int i = 0; i < LAYER_COUNT; i++)
				{
					C_AnimationLayer* pLayer = m_pPlayer->GetAnimOverlay(i, false);
					if (pLayer && pLayer->m_nSequence == 0)
						pLayer->SetWeight(0.f);
				}

				m_pPlayer->SetAbsAngles(QAngle(0.f, m_flGoalFeetYaw, 0.f));

				m_pLastActiveWeapon = m_pActiveWeapon;

				m_vecLastOrigin.x = m_vecOrigin.x;
				m_vecLastOrigin.y = m_vecOrigin.y;
				m_vecLastOrigin.z = m_vecOrigin.z;

				m_bFirstRunSinceInit = false;

				m_flLastUpdateTime = g_pGlobals->m_flCurTime;

				m_pPlayer->EnableInvalidateBoneCache(true);

				m_nLastUpdateFrame = g_pGlobals->m_nFrameCount;
				return;
			}
		}
	}
}

void CCSGOPlayerAnimState::ApplyLayerOrderPreset(int* pNewPreset, bool bForce)
{
	if (bForce || m_pLayerOrderPreset != pNewPreset)
	{
		m_pLayerOrderPreset = pNewPreset;

		for (int i = 0; i < LAYER_COUNT; ++i)
		{
			v5 = v3->m_pPlayer;
			if (*((_DWORD*)v5 + 2663))
			{
				C_AnimationLayer* pLayer = m_pPlayer->GetAnimOverlay(m_pLayerOrderPreset[i], false);
				if (pLayer)
				{
					pLayer->SetOrder(i);

					pLayer->m_pDispatchedStudioHdr = 0;
					pLayer->m_nDispatchedSrc = ACT_INVALID;
					pLayer->m_nDispatchedDst = ACT_INVALID;
				}
			}
		}
	}
}

int* g_pDefaultAnimLayerOrder;
int* g_pWeponPostAnimlayer;

void CCSGOPlayerAnimState::UpdateLayerOrderPreset(int nLayer, int nSequence)
{
	if (m_pPlayer && nLayer == LAYER_WEAPON_ACTION)
	{
		(*(void(__thiscall**)(int))(*(_DWORD*)g_pMdlCache + 132))(g_pMdlCache); // BeginLock
		if (!*((_DWORD*)m_pPlayer + 2644) && (*(int(__thiscall**)(int))(*((_DWORD*)m_pPlayer + 1) + 32))((int)m_pPlayer + 4))
			sub_101CA150();

		v7 = (_DWORD*)*((_DWORD*)m_pPlayer + 2644);
		if (!v7 || !*v7)
			v7 = 0;

		if (m_pPlayer->GetAnySequenceAnimTag(nSequence, ANIMTAG_FLASHBANG_PASSABLE, 0) != 0)
			ApplyLayerOrderPreset(g_pDefaultAnimLayerOrder, false);
		else
			ApplyLayerOrderPreset(g_pWeponPostAnimlayer, false);

		(*(void(__thiscall**)(int))(*(_DWORD*)g_pMdlCache + 136))(g_pMdlCache); // EndLock
	}
}

void CCSGOPlayerAnimState::UpdateAnimLayer(int nLayer, int nSequence, float flPlaybackRate, float flWeight, float flCycle)
{
	if (nSequence > 1)
	{
		(*(void(__thiscall**)(int))(*(_DWORD*)g_pMdlCache + 132))(g_pMdlCache); // BeginLock

		if (*((_DWORD*)m_pPlayer + 2663))
		{
			C_AnimationLayer* pLayer = m_pPlayer->GetAnimOverlay(nLayer, false);
			if (!pLayer)
				return;

			pLayer->SetSequence(nSequence);
			pLayer->SetPlaybackRate(flPlaybackRate);
			pLayer->SetCycle(std::clamp(flCycle, 0.f, 1.f));
			pLayer->SetWeight(std::clamp(flWeight, 0.f, 1.f));

			UpdateLayerOrderPreset(nLayer, nSequence);
		}

		(*(int(__thiscall**)(int))(*(_DWORD*)v5 + 136))(v5); // EndLock
	}
}

void CCSGOPlayerAnimState::SetLayerSequence(int nlayer, int nSequence)
{
	if (nSequence <= 1)
		return;

	C_AnimationLayer* pLayer = m_pPlayer->GetAnimOverlay(nlayer, false);
	if (!pLayer)
		return;

	pLayer->SetSequence(nSequence);
	pLayer->SetPlaybackRate(m_pPlayer->GetLayerSequenceCycleRate(nlayer, nSequence));
	pLayer->SetCycle(0.f);
	pLayer->SetWeight(0.f);
}