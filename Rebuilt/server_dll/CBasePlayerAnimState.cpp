#include "CBasePlayerAnimState.h"
#include "../mixed/CGlobalVarsBase.h"

const QAngle& CBasePlayerAnimState::GetRenderAngles()
{
    return m_angRender;
}

void CBasePlayerAnimState::ClearAnimationState()
{
    ClearAnimationLayers();
    m_bCurrentFeetYawInitialized = false;
    m_flLastAnimationStateClearTime = g_pServerGlobals->m_flCurTime;
}

void CBasePlayerAnimState::ClearAnimationLayers()
{
    if (!m_pOuter)
        return;

    for (int i = 0; i < m_pOuter->GetNumAnimOverlays(); i++)
    {
        m_pOuter->m_AnimOverlay[i]->m_nOrder = LAYER_COUNT;
        m_pOuter->m_AnimOverlay[i]->m_fFlags = 0;
    }
}

bool CBasePlayerAnimState::ShouldResetGroundSpeed(int nOldActivity, int nNewAct)
{
    return (nOldActivity == ACT_CROUCHIDLE
        || nOldActivity == ACT_IDLE
        || nOldActivity == ACT_TURN
        || nOldActivity == ACT_STEP_FORE)
        && (nNewAct == ACT_WALK || nNewAct == ACT_RUN_CROUCH || nNewAct == ACT_WALK_CROUCH || nNewAct == ACT_RUN);
}

void CBasePlayerAnimState::SetForceAimYaw(bool m_bForce)
{
    m_bForceAimYaw = m_bForce;
}

bool CBasePlayerAnimState::ShouldBlendAimSequenceToIdle()
{
    int v1 = m_nCurrentMainSequenceActivity;
    return v1 == ACT_RUN
        || v1 == ACT_LEAP
        || v1 == ACT_WALK
        || v1 == ACT_JUMP
        || v1 == ACT_RUNTOIDLE
        || v1 == ACT_RUN_CROUCH
        || v1 == ACT_WALK_CROUCH;
}

float CBasePlayerAnimState::GetFeetYawRate()
{
    return mp_feetyawrate.GetFloat();
}