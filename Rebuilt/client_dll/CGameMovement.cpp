#include "CGameMovement.h"

#include "../mixed/CUserCmd.h"
#include "../mixed/EntityStuff.h"
#include "../mixed/CGlobalVarsBase.h"
#include "../mixed/C_CSPlayer.h"
#include "C_CSGameRules.h"

void CGameMovement::ProcessMovement(C_BasePlayer* pPlayer, CMoveData* pMoveData)
{
    m_nTraceCount = 0;
    float flBackupFrameTime = g_pGlobals->m_flFrameTime;
    g_pGlobals->m_flFrameTime = pPlayer->m_flLaggedMovementValue * g_pGlobals->m_flFrameTime;

    ResetGetWaterContentsForPointCache();

    m_pMoveData = pMoveData;
    m_nSpeedCropped = SPEED_CROPPED_RESET;
    m_pPlayer = pPlayer;
    m_pMoveData->m_flMaxSpeed = pPlayer->GetPlayerMaxSpeed();
    m_bProcessingMovement = true;

    DiffPrint("start %f %f %f", m_pMoveData->m_vecAbsOrigin.x, m_pMoveData->m_vecAbsOrigin.y, m_pMoveData->m_vecAbsOrigin.z);

    PlayerMove();
    m_pMoveData->m_nOldButtons = m_pMoveData->m_nButtons;

    DiffPrint("end %f %f %f", m_pMoveData->m_vecAbsOrigin.x, m_pMoveData->m_vecAbsOrigin.y, m_pMoveData->m_vecAbsOrigin.z);
    g_pGlobals->m_flFrameTime = flBackupFrameTime;

    m_bProcessingMovement = false;
}

void CGameMovement::Reset()
{
    m_pPlayer = nullptr;
}

const Vector& CGameMovement::GetPlayerMins(bool bDucked)
{
    CViewVectors* v1 = g_pGameRules->GetViewVectors();

    return bDucked ? v1->m_vecDuckHullMin : v1->m_vecHullMin;
}

const Vector& CGameMovement::GetPlayerMaxs(bool bDucked)
{
    CViewVectors* v1 = g_pGameRules->GetViewVectors();

    return bDucked ? v1->m_vecDuckHullMax : v1->m_vecHullMax;
}



void CGameMovement::ResetGetWaterContentsForPointCache()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 64; j++)
            m_nCachedGetPointContents[j][i] = -9999;
    }
}

// ======================== //
// ======================== //
// ======================== //

bool CCSGameMovement::CanAccelerate()
{
    if (m_pCSPlayer->m_nPlayerState)
        return m_pPlayer->GetPlayerState() != 0;
    else
        return m_pPlayer->m_flWaterJumpTime == 0.0f;
}

void CCSGameMovement::Accelerate(Vector& vecWishDir, float flWishSpeed, float flAccelerate)
{
    if (!CanAccelerate())
        return;

    float v6 = m_pMoveData->m_vecVelocity.Length();
    float v63 = flWishSpeed - v6;

    if (v63 > 0.0f)
    {
        float flCurrentSpeed = fmaxf(v6, 0.0f);

        bool bIsDucking = true;
        if (!m_pMoveData->m_nButtons & IN_DUCK)
        {
            if (!m_pPlayer->m_bDucking && !m_pPlayer->m_fFlags & FL_DUCKING)
                bIsDucking = false;
        }

        bool bIsWalking = true;
        if (!m_pMoveData->m_nButtons & IN_SPEED || bIsDucking)
            bIsWalking = false;

        float flAccelerationScale = fmaxf(flWishSpeed, 250.f);
        
        if (!m_pPlayer || !m_pPlayer->IsAlive())
            m_pPlayer = nullptr;

        CWeaponCSBase* pWeapon = dynamic_cast<CWeaponCSBase*>(m_pPlayer->GetActiveWeapon());

        bool v51 = false;
        float v53 = 1.0f;

        if (sv_accelerate_use_weapon_speed.GetBool() && pWeapon)
        {
            float v52 = 1.35f;
            if (!*((int*)m_pCSPlayer + 70565))
                v52 = 1.0f;

            float v56 = ((float(__thiscall*)(CWeaponCSBase*))*(_DWORD*)(*(_DWORD*)pWeapon + 1768))(pWeapon) * v52; // Maxspeed i think
            bool bIsSlowSniperScoped = false;

            if (pWeapon->GetCSZoomLevel() > 0)
            {
                if (pWeapon->GetZoomLevels() > 1 && v56 * CS_PLAYER_SPEED_WALK_MODIFIER < 110.f)
                    bIsSlowSniperScoped = true;
            }

            float flZeroToMaxSpeedTime = fminf(v56 * 0.004, 1.0);
            if (!bIsDucking && !bIsWalking || bIsSlowSniperScoped)
                v53 = flZeroToMaxSpeedTime;

            float flGoalSpeed;

            if (sv_weapon_encumbrance_scale.GetFloat() != 0.0f && m_pPlayer)
            {
                m_pPlayer->sub_103FE260();


                if (flZeroToMaxSpeedTime > sv_weapon_encumbrance_scale.GetFloat())
                {
                    v51 = true;

                    flZeroToMaxSpeedTime = flZeroToMaxSpeedTime + (sv_weapon_encumbrance_scale.GetFloat() - flZeroToMaxSpeedTime)
                        * sv_weapon_encumbrance_scale.GetFloat();

                    flGoalSpeed = fmaxf(flZeroToMaxSpeedTime, CS_PLAYER_SPEED_DUCK_MODIFIER) * flAccelerationScale;
                }
                else
                    flGoalSpeed = flZeroToMaxSpeedTime * flAccelerationScale;
            }
            else
                flGoalSpeed = flAccelerationScale;

            float v19 = v53;
            if (bIsDucking)
            {
                v19 = fminf(v53, CS_PLAYER_SPEED_DUCK_MODIFIER);
                flGoalSpeed *= CS_PLAYER_SPEED_DUCK_MODIFIER;
            }

            float flAccelExponentTop = v19 * flAccelerationScale;
            float v54 = flAccelExponentTop;

            if (bIsWalking)
            {
                if (!*((int*)m_pPlayer + 70593) && !sub_101A5DA0((unsigned int*)m_pPlayer + 16658, 0) && !bIsSlowSniperScoped)
                {
                    flAccelExponentTop *= CS_PLAYER_SPEED_WALK_MODIFIER;
                    v54 = flAccelExponentTop;
                }

                flGoalSpeed *= CS_PLAYER_SPEED_WALK_MODIFIER;
            }

            float v23 = 0.0f;
            float flSurfaceFriction = m_pPlayer->m_surfaceFriction;
            float flMaxAccelSpeed = (g_pGlobals->m_flFrameTime * flAccelerate) * flAccelExponentTop;

            if (v51 && flCurrentSpeed > (flGoalSpeed - flMaxAccelSpeed))
            {
                float v27 = 1.0f - fmaxf(flCurrentSpeed - flMaxAccelSpeed, 0.0f) / fmaxf(flGoalSpeed - flMaxAccelSpeed, 0.0f);
                flAccelExponentTop = v54;

                if (v27 >= 0.0f)
                    flAccelerate *= fminf(v27, 1.0f);
                else
                    flAccelerate *= 0.0f; // Lmao
            }

            float flStoreAcceleration;

            if (bIsWalking && flCurrentSpeed > (flGoalSpeed - 5.0f))
            {
                float v28 = fmaxf(flCurrentSpeed - (flGoalSpeed - 5.0f), 0.0f) / fmaxf(flGoalSpeed - (flGoalSpeed - 5.0f), 0.0f);
                if ((1.0 - v28) >= 0.0)
                    flStoreAcceleration = fminf(1.0 - v28, 1.0) * flAccelerate;
                else
                    flStoreAcceleration = 0.0f * flAccelerate; // Lmao
            }
            else
                flStoreAcceleration = flAccelerate;

            float v30 = fminf(((g_pGlobals->m_flFrameTime * flStoreAcceleration) * flAccelExponentTop) * flSurfaceFriction, v63);
            v63 = v30;

            if (m_pPlayer)
            {
                float v31 = *((float*)m_pPlayer + 0x4106) - g_pGlobals->m_flCurTime;
                float v32;
                float v32;

                if (v31 >= 0.0f && fminf(v31, 1.0f) > 0.0f)
                {
                    v23 = 0.0f;
                    v30 = v63;
                    v32 = healthshot_healthboost_speed_multiplier.GetFloat();

                    float v33 = *((float*)m_pPlayer + 16646) - g_pGlobals->m_flCurTime;
                    if (v33 >= 0.0f)
                        v23 = fminf(v33, 1.0);

                    v30 *= ((v32 - 1.0f) * v23) + 1.0f;
                }
            }

            m_pMoveData->m_vecVelocity += vecWishDir * v30;
            v63 = *((float*)m_pCSPlayer + 16636);
            
            if (v63 != g_pGlobals->m_flCurTime)
                v63 = g_pGlobals->m_flCurTime;

            Vector v41 = m_pMoveData->m_vecTrailingVelocity;
            if (v41.x > -0.01f && v41.x < 0.01f
                && (v41.y = m_pMoveData->m_vecTrailingVelocity.y, v41.y > -0.01f)
                && v41.y < 0.01f
                && (v41.z = m_pMoveData->m_vecTrailingVelocity.z, v41.z > -0.01f)
                && v41.z < 0.01f
                || (g_pGlobals->m_flCurTime - m_pMoveData->m_flTrailingVelocityTime) > 0.35f)
            {
                m_pMoveData->m_vecTrailingVelocity = m_pMoveData->m_vecVelocity;
                m_pMoveData->m_flTrailingVelocityTime = g_pGlobals->m_flCurTime;
                return;
            }

            float v45 = m_pMoveData->m_vecTrailingVelocity.Length2D();
            if (v45 > 0.8f)
            {
                if (m_pMoveData->m_vecVelocity.Length2D() <= m_pMoveData->m_vecTrailingVelocity.Length2D())
                {
                    m_pMoveData->m_vecTrailingVelocity = m_pMoveData->m_vecVelocity;
                    m_pMoveData->m_flTrailingVelocityTime = g_pGlobals->m_flCurTime;
                    return;
                }
            }

            if (v45 < -0.8
                && sqrtf(
                    (m_pMoveData->m_vecTrailingVelocity.x * m_pMoveData->m_vecTrailingVelocity.x)
                    + (m_pMoveData->m_vecTrailingVelocity.y * m_pMoveData->m_vecTrailingVelocity.y)) < 225.0f
                && sqrtf(
                    (m_pMoveData->m_vecTrailingVelocity.x * m_pMoveData->m_vecTrailingVelocity.x)
                    + (m_pMoveData->m_vecTrailingVelocity.y * m_pMoveData->m_vecTrailingVelocity.y)) > 115.0f
                && sqrtf((m_pMoveData->m_vecVelocity.x * m_pMoveData->m_vecVelocity.x) + (m_pMoveData->m_vecVelocity.y
                    * m_pMoveData->m_vecVelocity.y)) > 115.0)
            {
                sub_101AC3F0(&m_pMoveData->m_vecTrailingVelocity, 0, 0);
                float v65 = m_pMoveData->m_vecTrailingVelocity.Length2D();
                if (v65 > -0.3 && v65 < 0.3)
                {
                    C_BaseCombatWeapon* pWeapon_1 = m_pCSPlayer->GetActiveWeapon();

                    if (pWeapon_1)
                    {
                        m_pMoveData->m_vecTrailingVelocity = m_pMoveData->m_vecVelocity;
                        m_pMoveData->m_flTrailingVelocityTime = g_pGlobals->m_flCurTime;
                    }
                }
            }
        }
    }
}