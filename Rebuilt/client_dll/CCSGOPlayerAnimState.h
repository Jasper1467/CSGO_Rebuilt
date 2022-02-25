#pragma once

#include "../mixed/Vectors.h"
#include "../client_dll/C_CSPlayer.h"
#include "../mixed/Studio.h"
#include "../mixed/AnimationStuff.h"
#include "../engine_dll/CEngineClient.h"
#include "../mixed/EntityStuff.h"
#include "C_BaseAnimating.h"
#include "../mixed/CUtlVector.h"

inline bool IsPreCrouchUpdateDemo()
{
	return g_pEngineClient->IsHLTV() || g_pEngineClient->IsPlayingDemo()
		&& (*(int(__thiscall**)(int))(*(_DWORD*)g_pEngineClient + 904))(g_pEngineClient) <= 13546;
}

class CBasePlayerAnimState
{
public:
	char pad0[24];
	C_BaseAnimating* m_pOuter;
};

class CCSPlayerAnimState : CBasePlayerAnimState
{
public:

};

struct C_AnimationLayer
{
	float m_flLayerAnimtime;
	float m_flLayerFadeOuttime;
	CStudioHdr* m_pDispatchedStudioHdr;
	Activity_t m_nDispatchedSrc;
	Activity_t m_nDispatchedDst;
	int m_nOrder;
	int m_nSequence;
	float m_flPrevCycle;
	float m_flWeight;
	float m_flWeightDeltaRate;
	float m_flPlaybackRate;
	float m_flCycle;
	C_BaseAnimating* m_pOwner;
	int m_nInvalidatePhysicsBits;

	void SetOrder(int nOrder)
	{
		if (m_pOwner)
		{
			if (m_nOrder != nOrder && m_nOrder == 15)
				m_pOwner->InvalidatePhysicsRecursive(BOUNDS_CHANGED);
		}
	}

	void SetWeight(float flWeight)
	{
		if (m_pOwner)
		{
			if (flWeight != 0.0)
				m_pOwner->InvalidatePhysicsRecursive(BOUNDS_CHANGED);
		}

		flWeight = 0.0;
	}

	void SetSequence(int nSequence)
	{
		if (m_pOwner)
		{
			if (nSequence != 0)
				m_pOwner->InvalidatePhysicsRecursive(BOUNDS_CHANGED);
		}

		nSequence = 0;
	}

	void SetCycle(float flCycle)
	{
		if (m_pOwner)
		{
			if (flCycle != 0.0)
				m_pOwner->InvalidatePhysicsRecursive(ANIMATION_CHANGED);
		}

		flCycle = 0.0;
	}

	void SetPlaybackRate(float flPlaybackRate)
	{
		m_flPlaybackRate = flPlaybackRate;
	}
};

class C_BaseCombatWeapon;

// NOTE: No vtable
class CCSGOPlayerAnimState
{
public:
	void Update(QAngle& angView);

	void SetupVelocity();
	void SetupAimMatrix();
	void SetupWeaponAction();
	void SetupMovement();
	void SetupAliveloop();
	void SetupWholeBodyAction();
	void SetUpFlashedReaction();
	void SetupFlinch();
	void SetupLean();

	void ApplyLayerOrderPreset(int* pNewPreset, bool bForce);
	void UpdateLayerOrderPreset(int nLayer, int nSequence);
	void UpdateAnimLayer(int nLayer, int nSequence, float flPlaybackRate, float flWeight, float flCycle);

	void SetLayerSequence(int nlayer, int nSequence);

	bool CacheSequences();

	int* m_pLayerOrderPreset;
	bool m_bFirstRunSinceInit;
	bool m_bFirstFootPlantSinceInit;
	char pad[2];
	int m_nUnknownInt;
	float m_flEyePositionSmoothLerp;
	float m_flStrafeChangeWeightSmoothFalloff;
	aimmatrix_transition_t m_StandWalkAim;
	aimmatrix_transition_t m_StandRunAim;
	aimmatrix_transition_t m_CrouchWalkAim;
	int m_nUnknownArray[3];
	int m_nModelIndex;
	C_CSPlayer* m_pPlayer;
	C_BaseCombatWeapon* m_pActiveWeapon;
	C_BaseCombatWeapon* m_pLastActiveWeapon;
	float m_flLastUpdateTime;
	int m_nLastUpdateFrame;
	float m_flLastUpdateIncrement;
	float m_flEyeYaw;
	float m_flEyePitch;
	float m_flGoalFeetYaw;
	float m_flCurrentFeetYaw;
	float m_flMoveYawIdeal;
	float m_flGoalMoveDirGoalFeetDelta;
	float m_flMoveYawCurrentToIdeal;
	float pad_0049;
	float m_flFeetCycle;
	float m_flFeetWeight;
	float m_flUnknown2;
	float m_flDuckAmount;
	float m_flDuckAdditional;
	float m_flMoveWeight;
	Vector m_vecOrigin;
	Vector m_vecLastOrigin;
	Vector m_vecVelocity;
	Vector m_vecVelocityNormalized;
	Vector m_vecLastAcceleratingVelocity;
	float m_flSpeed;
	float m_flAbsVelocityZ;
	float m_flSpeedAsPortionOfRunTopSpeed;
	float m_flRunningSpeed;
	float m_flDuckingSpeed;
	float m_flTimeSinceStartedMoving;
	float m_flTimeSinceStoppedMoving;
	bool m_bOnGround;
	bool m_bLanding;
	char pad_010A[2];
	float m_flNextLowerBodyYawUpdateTime;
	float m_flDurationInAir;
	float m_flLeftGroundHeight;
	float m_flHitGroundWeight;
	float m_flGroundFraction;
	bool m_bLandedOnGroundThisFrame;
	bool m_bLeftTheGroundThisFrame;
	char pad_0120[2];
	float m_flInAirSmoothValue;
	bool m_bOnLadder;
	char pad_0128[3];
	float m_flLandAnimMultiplier;
	float m_flWalkToRunTransition;
	bool m_bNotRunning;
	char pad_0135[3];
	bool m_bInBalanceAdjust;
	char pad_0141[3];
	CUtlVector<void*/*CUtlSymbol*/> m_ActivityModifiers;
	float m_flLadderWeight;
	int m_flLadderSpeed;
	float m_flTimeOfLastInjury;
	float m_flLastSetupLeanCurtime;
	Vector m_vecLastSetupLeanVelocity;
	Vector m_vecSetupLeanVelocityDelta;
	Vector m_vecSetupLeanVelocityInterpolated;
	float m_flLeanWeight;
	Vector m_vecTargetAcceleration;
	char pad_qzdqzdzqd[3];
	float m_flStrafeWeight;
	Vector m_vecAcceleration;
	float m_flStrafeCycle;
	float m_flStrafeChangeWeight;
	bool m_bStrafing;
	char m_bStrafingPad[3];
	float m_flStrafeChangeCycle;
	int m_nStrafeSequence;
	bool m_bUnknownBool__;
	bool m_bIsAccelerating;
	char pad_01AE[2];
	animstate_pose_param_cache_t m_arrPoseParameters[20];
	int m_iUnknownClientInt__;
	float m_flStaticApproachSpeed;
	int m_iMoveState;
	float m_flMovePlaybackRate;
	float m_flUnknownFL0;
	float m_flUnknownFL;
	float m_flUnknownFL1;
	float m_flMinYawServer;
	float m_flMaxYawServer;
	float m_flMaximumPitchServer;
	float m_flMinimumPitchServer;
	int m_iUnknownInt;
	char pad_02D0[84];
	float m_flEyePosZ;
	bool m_bIsDucked;
	char pad_0329[3];
	float m_flUnknownCap1;
	float m_flMinYaw;
	float m_flMaxYaw;
	float m_flMinPitch;
	float m_flMaxPitch;
	int m_nAnimsetVersion;
};