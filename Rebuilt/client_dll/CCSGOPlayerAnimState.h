#pragma once

#include "../mixed/Vectors.h"
#include "../client_dll/C_BaseEntity.h"
#include "../mixed/Studio.h"
#include "../mixed/CCSGOPlayerAnimState.h"
#include "../engine_dll/CEngineClient.h"

inline bool IsPreCrouchUpdateDemo()
{
	return g_pEngineClient->IsHLTV() || (*(unsigned __int8(__thiscall**)(int))(*(_DWORD*)g_pEngineClient + 328))(g_pEngineClient))
		&& (*(int(__thiscall**)(int))(*(_DWORD*)g_pEngineClient + 904))(g_pEngineClient) <= 13546;
}

class C_BaseAnimating;

class CCSPlayerAnimState : CBasePlayerAnimState
{
public:

};

class CBasePlayerAnimState
{
public:
	char pad0[24];
	C_BaseAnimating* m_pOuter;
};

struct C_AnimationLayer
{
	float m_flLayerAnimtime;
	float m_flLayerFadeOuttime;
	CStudioHdr* m_pDispatchedStudioHdr;
	Activities_t m_nDispatchedSrc;
	Activities_t m_nDispatchedDst;
	int m_nOrder;
	int m_nSequence;
	float m_flPrevCycle;
	float m_flWeight;
	float m_flWeightDeltaRate;
	float m_flPlaybackRate;
	float m_flCycle;
	void* m_pOwner;
	int m_nInvalidatePhysicsBits;
};

class CCSGOPlayerAnimState
{
public:
	bool m_bFirstRunSinceInit;
	char pad0[3];
	float m_flFlashedStartTime;
	float m_flFlashedEndTime;
	aimmatrix_transition_t m_StandWalkAim;
	aimmatrix_transition_t m_StandRunAim;
	aimmatrix_transition_t m_CrouchWalkAim;
	int m_nModelIndex;
	void* m_pBaseEntity;
	void* m_pActiveWeapon;
	void* m_pLastActiveWeapon;
	float m_flLastClientSideAnimationUpdateTime;
	int m_nLastClientSideAnimationUpdateFramecount;
	float m_flLastClientSideAnimationUpdateTimeDelta;
	float m_flEyeYaw;
	float m_flEyePitch;
	float m_flGoalFeetYaw;
	float m_flCurrentFeetYaw;
	float m_flCurrentMoveDirGoalFeetDelta;
	float m_flGoalMoveDirGoalFeetDelta;
	float m_flFeetVelDirDelta;
	float pad_0049;
	float m_flFeetCycle;
	float m_flFeetWeight;
	float m_flUnknown2;
	float m_flDuckAmount;
	float m_flHitGroundCycle;
	float m_fUnknown3;
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
	float m_flDuckRate;
	bool m_bOnLadder;
	char pad_0128[3];
	float m_flLadderWeight;
	float m_flLadderSpeed;
	bool m_bNotRunning;
	char pad_0135[3];
	bool m_bInBalanceAdjust;
	char pad_0141[3];
	void* m_ActivityModifiers;
	int gap148[1];
	float m_flTimeOfLastInjury;
	float m_flLastSetupLeanCurtime;
	Vector m_vecLastSetupLeanVelocity;
	Vector m_vecSetupLeanVelocityDelta;
	Vector m_vecSetupLeanVelocityInterpolated;
	float m_flLeanWeight;
	Vector m_vecAcceleration;
	bool m_bFlashed;
	char m_bFlashedPad[3];
	float m_flStrafeWeight;
	int m_iUnknownint3;
	float m_flStrafeCycle;
	float m_flStrafeChangeWeight;
	bool m_bStrafing;
	char m_bStrafingPad[3];
	float m_flStrafeChangeCycle;
	int m_nStrafeSequence;
};