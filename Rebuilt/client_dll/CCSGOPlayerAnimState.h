#pragma once

#include "../mixed/Vectors.h"
#include "../client_dll/C_BaseEntity.h"
#include "../mixed/Studio.h"

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

enum AnimationLayers_t
{
	LAYER_AIMMATRIX = 0x0,
	LAYER_WEAPON_ACTION = 0x1,
	LAYER_WEAPON_ACTION_RECROUCH = 0x2,
	LAYER_ADJUST = 0x3,
	LAYER_MOVEMENT_JUMP_OR_FALL = 0x4,
	LAYER_MOVEMENT_LAND_OR_CLIMB = 0x5,
	LAYER_MOVEMENT_MOVE = 0x6,
	LAYER_MOVEMENT_STRAFECHANGE = 0x7,
	LAYER_WHOLE_BODY = 0x8,
	LAYER_FLASHED = 0x9,
	LAYER_FLINCH = 0xA,
	LAYER_ALIVELOOP = 0xB,
	LAYER_LEAN = 0xC,
	LAYER_COUNT = 0xD,
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
	char pad0[90];
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
	float m_flSpeedNormalized;
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
	float m_flLandAnimMultiplier;
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
	void* m_Modifiers;
	int gap148[1];
	float m_flTimeOfLastInjury;
	float m_flLastSetupLeanCurtime;
	Vector m_vecLastSetupLeanVelocity;
	Vector m_vecSetupLeanVelocityDelta;
	Vector m_vecSetupLeanVelocityInterpolated;
	float m_flLeanWeight;
	Vector m_vecAcceleration;
	bool m_flAccelerationWeight;
	char m_bFlashedPad[3];
	float m_flStrafeWeight;
	int m_iUnknownint3;
	float m_flStrafeCycle;
	int m_flStrafeChangeWeight;
	bool m_bStrafing;
	char m_bStrafingPad[3];
	float m_flStrafeChangeCycle;
	int m_nStrafeSequence;
};