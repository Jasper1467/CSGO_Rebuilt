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