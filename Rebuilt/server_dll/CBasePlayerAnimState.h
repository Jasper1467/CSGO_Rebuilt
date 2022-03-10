#pragma once

#include "../mixed/EntityStuff.h"
#include "../mixed/AnimationStuff.h"
#include "../mixed/Vectors.h"
#include "CBaseAnimating.h"

class CBasePlayerAnimState
{
public:
	void ClearAnimationState();
	const QAngle& GetRenderAngles();
	void SetForceAimYaw(bool bForce);
	void ClearAnimationLayers();
	bool ShouldBlendAimSequenceToIdle();
	bool ShouldResetGroundSpeed(int nOldActivity, int nNewAct);
	float GetFeetYawRate();
	void RestartMainSequence();

	char pad[2];
	float m_flMaxBodyYawDegrees;
	float m_flMaxBodyYawDegreesCorrectionAmount;
	char pad1[8];
	LegAnimType_e m_LegAnimType;
	bool m_bUseAimSequences;
	CBaseAnimatingOverlay* m_pOuter;
	float m_flEyeYaw;
	float m_flEyePitch;
	float m_flGoalFeetYaw;
	float m_flCurrentFeetYaw;
	bool m_bCurrentFeetYawInitialized;
	bool m_bForceAimYaw;
	char pad2[8];
	float m_flLastTurnTime;
	char pad3[4];
	QAngle m_angRender;
	Vector2D m_vecLastMovePose;
	char pad4[12];
	float m_flPoseParamTargetDampenedScaleIdeal;
	float m_flMaxGroundSpeed;
	float m_flLastAnimationStateClearTime;
	char pad5[8];
	Activity_e m_nCurrentMainSequenceActivity;
	float m_flGaitYaw;
};