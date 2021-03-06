#pragma once

#include "../mixed/AnimationStuff.h"
#include "../mixed/mathlib.h"
#include "../mixed/Vectors.h"
#include "../mixed/EntityStuff.h"
#include "CCSPlayer.h"

class CBaseEntity;
class CBaseCombatWeapon;

// Fucked some things up here :(
class CCSGOPlayerAnimState
{
public:
	void IncrementLayerCycle(int nLayer, bool a3);

	int* m_pLayerOrderPreset;
	bool m_bFirstRunSinceInit;
	char pad[3];
	float m_flFlashedAmountEaseOutStart;
	float m_flFlashedAmountEaseOutEnd;
	aimmatrix_transition_t m_StandWalkAim;
	aimmatrix_transition_t m_StandRunAim;
	aimmatrix_transition_t m_CrouchWalkAim;
	int m_nModelIndex;
	CCSPlayer* m_pPlayer;
	CBaseCombatWeapon* m_pActiveWeapon;
	CBaseCombatWeapon* m_pLastActiveWeapon;
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
	float pad_0094;
	float m_flFeetCycle;
	float m_flFeetWeight;
	float m_fUnknown2;
	float m_fDuckAmount;
	float m_flHitGroundCycle;
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
	bool m_bJumping;
	char pad_010A[2];
	float m_flNextLowerBodyYawUpdateTime;
	bool m_bInParachute;
	bool m_bInHitGroundAnimation;
	char PAD_FUCKER[2];
	int m_iUnknownIntBlah;
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
	bool m_bDefusing;
	bool m_bPlantingBomb;
	char pad_0135;
	bool m_bInBalanceAdjust;
	char pad_0141[3];
	void* m_ActivityModifiers;
	float m_flLadderWeight;
	int m_flLadderSpeed;
	float m_flTimeOfLastInjury;
	float m_flLastSetupLeanCurtime;
	Vector m_vecLastSetupLeanVelocity;
	Vector m_vecSetupLeanVelocityDelta;
	Vector m_vecSetupLeanVelocityInterpolated;
	float m_flLeanWeight;
	Vector m_vecTargetAcceleration;
	char m_anotherpad[3];
	float m_flStrafeWeight;
	bool m_bFlashed;
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
	bool m_bDeploying;
	int m_iUnknownInt__;
	float m_flGoalRunningSpeed;
	int m_iMoveState;
	float m_flMovePlaybackRate;
	float m_flUnknownFL0;
	float m_flMinYaw;
	float m_flMaxYaw;
	float m_flMinPitch;
	float m_flMaxPitch;
	int m_iAnimsetVersion;
};
