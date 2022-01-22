#include "C_BasePlayer.h"

#include "../mixed/EntityStuff.h"
#include "../engine_dll/CEngineClient.h"

#include "../engine_dll/ConVar.h"
#include "CPrediction.h"

ConVar cl_smooth = ConVar("cl_smooth", "0", 0, "Smooth view/eye origin after prediction errors");
ConVar cl_smoothtime = ConVar("cl_smoothtime", "0.1", 0x40000000, "Smooth view/eye origin after prediction errors");

bool C_BasePlayer::IsAlive()
{
	return m_lifeState == LIFE_ALIVE;
}

void C_BasePlayer::GetPredictionErrorSmoothingVector(Vector vecOffset)
{
	if (g_pEngineClient->IsPlayingDemo() || !cl_smooth.GetBool() || !cl_predict.GetBool() || g_pEngineClient->IsPaused())
	{
		vecOffset.Reset();
		return;
	}
	else
	{
		float flErrorAmount = (g_pGlobals->m_flCurTime - m_flPredictionErrorTime) / cl_smoothtime.GetFloat();
		if (flErrorAmount < 1.0f)
		{
			flErrorAmount -= 1.f;
			vecOffset = m_vecPredictionError * flErrorAmount;
		}
	}
}

ConVar cl_use_new_headbob = ConVar("cl_use_new_headbob", "4", 0x4000, "");
ConVar cl_headbob_land_dip_amt = ConVar("cl_headbob_land_dip_amt", "4", 0x8, "");

void C_BasePlayer::CalcViewBob(Vector& vecEyeOrigin)
{
    if (!cl_use_new_headbob.GetBool())
        return;

    if (m_flFallVelocity <= 0.1 && m_flOldFallVelocity > 10.f && m_flOldFallVelocity <= 1024.f && !m_bInLanding)
    {
        m_bInLanding = true;
        m_flLandingTime = g_pGlobals->m_flCurTime;
    }

    if (m_bInLanding)
    {
        float v5 = fmaxf(g_pGlobals->m_flCurTime - m_flLandingTime, 0.0) * 4.0;

        (*(void(__thiscall**)(C_BasePlayer*))(*(_DWORD*)v2 + 700))(v2); // ????

        float v10 = ((v5 * v5) * 3.f) - (((v5 * v5) * 2.f) * v5);
        float v7 = (float)((float)((float)(int)(64.f - cl_headbob_land_dip_amt.GetInt()) 
            - (float)(0.1 / m_flOldFallVelocity)) * v10) + (float)((float)(1.0 - v10) * 64.f);

        if (v7 > 64.0)
        {
            v7 = 64.0;
            m_bInLanding = 0;
        }

        vecEyeOrigin.z -= (64.f - v7);

        if (m_bInLanding && (vecEyeOrigin.z - 0.001) >= vecEyeOrigin.z)
            v2[m_bInLanding] = 0;
    }

    if (!m_bInLanding)
       m_flOldFallVelocity = m_flFallVelocity;
}

void C_BasePlayer::SetPlayerUnderwater(bool bState)
{
    if (m_bPlayerUnderwater != bState)
    {
        m_bPlayerUnderwater = bState;

        if (bState)
            EmitSound("Player.AmbientUnderWater", this);
        else
            StopSound(this, "Player.AmbientUnderWater");
    }
}

float C_BasePlayer::GetPlayerMaxSpeed()
{
    float result = sv_maxspeed.GetFloat();

    if (m_flMaxspeed > 0.0)
        result = fminf(m_flMaxspeed, result);

    return result;
}

void C_BasePlayer::NotePredictionError(Vector& vecDelta)
{
    if (IsAlive() || *(_BYTE*)&v2[39649])
    {
        Vector vecSmoothening;
        GetPredictionErrorSmoothingVector(vecSmoothening);
        m_vecPredictionError = vecDelta + vecSmoothening;

        m_flPredictionErrorTime = g_pGlobals->m_flCurTime;
        ResetLatched();
    }
}