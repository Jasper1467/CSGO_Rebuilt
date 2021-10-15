#pragma once

#include "../mixed/CBasePlayerAnimState.h"

class CBaseAnimatingOverlay;

class CBasePlayerAnimState
{
public:
	char pad[2];
	float m_flMaxBodyYawDegrees;
	float m_flMaxBodyYawDegreesCorrectionAmount;
	char pad1[8];
	LegAnimType_t m_LegAnimType;
	bool m_bUseAimSequences;
	CBaseAnimatingOverlay* m_pOuter;
	float m_flEyeYaw;
	float m_flEyePitch;
	float m_flGoalFeetYaw;
	float m_flCurrentFeetYaw;
};