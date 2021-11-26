#pragma once

#include "mathlib.h"
#include "../engine_dll/ConVar.h"

struct aimmatrix_transition_t
{
	float m_flDurationStateHasBeenValid;
	float m_flDurationStateHasBeenInValid;
	float m_flHowLongToWaitUntilTransitionCanBlendIn;
	float m_flHowLongToWaitUntilTransitionCanBlendOut;
	float m_flBlendValue;

	void UpdateTransitionState(float flTimeInterval, float flSpeed, bool bStateShouldBeValid)
	{
		if (bStateShouldBeValid)
		{
			m_flDurationStateHasBeenInValid = 0.f;
			m_flDurationStateHasBeenValid += flTimeInterval;

			if (m_flDurationStateHasBeenValid >= m_flHowLongToWaitUntilTransitionCanBlendIn)
				m_flBlendValue = Approach(1.f, m_flBlendValue, flSpeed);
		}
		else
		{
			m_flDurationStateHasBeenValid = 0.f;
			m_flDurationStateHasBeenInValid += flTimeInterval;

			if (m_flDurationStateHasBeenInValid >= m_flHowLongToWaitUntilTransitionCanBlendOut)
				m_flBlendValue = Approach(0.f, m_flBlendValue, flSpeed);
		}
	}
};

struct animstate_pose_param_cache_t
{
	bool m_bInitialized;
	char pad_01[3];
	int m_nIndex;
	char* m_szPoseParameter;
};

enum AnimationLayer_t
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

enum AnimLayerFlag_t
{
	ANIM_LAYER_FLAG_ACTIVE = 0x1,
	ANIM_LAYER_FLAG_AUTOKILL = 0x2,
	ANIM_LAYER_FLAG_KILLME = 0x4,
	ANIM_LAYER_FLAG_DONTRESTORE = 0x8,
	ANIM_LAYER_FLAG_CHECKACCESS = 0x10,
	ANIM_LAYER_FLAG_DYING = 0x20,
	ANIM_LAYER_FLAG_NOEVENTS = 0x40,
};

enum LegAnimType_t
{
	LEGANIM_9WAY = 0x0,
	LEGANIM_8WAY = 0x1,
	LEGANIM_GOLDSRC = 0x2,
};

enum PlayerAnimEvent_t
{
	PLAYERANIMEVENT_FIRE_GUN_PRIMARY = 0x0,
	PLAYERANIMEVENT_FIRE_GUN_PRIMARY_OPT = 0x1,
	PLAYERANIMEVENT_FIRE_GUN_PRIMARY_SPECIAL1 = 0x2,
	PLAYERANIMEVENT_FIRE_GUN_PRIMARY_OPT_SPECIAL1 = 0x3,
	PLAYERANIMEVENT_FIRE_GUN_SECONDARY = 0x4,
	PLAYERANIMEVENT_FIRE_GUN_SECONDARY_SPECIAL1 = 0x5,
	PLAYERANIMEVENT_GRENADE_PULL_PIN = 0x6,
	PLAYERANIMEVENT_THROW_GRENADE = 0x7,
	PLAYERANIMEVENT_JUMP = 0x8,
	PLAYERANIMEVENT_RELOAD = 0x9,
	PLAYERANIMEVENT_RELOAD_START = 0xA,
	PLAYERANIMEVENT_RELOAD_LOOP = 0xB,
	PLAYERANIMEVENT_RELOAD_END = 0xC,
	PLAYERANIMEVENT_CLEAR_FIRING = 0xD,
	PLAYERANIMEVENT_DEPLOY = 0xE,
	PLAYERANIMEVENT_SILENCER_ATTACH = 0xF,
	PLAYERANIMEVENT_SILENCER_DETACH = 0x10,
	PLAYERANIMEVENT_THROW_GRENADE_UNDERHAND = 0x11,
	PLAYERANIMEVENT_CATCH_WEAPON = 0x12,
	PLAYERANIMEVENT_COUNT = 0x13,
};

#define ANIM_MOVING_MINIMUM_SPEED 0.5f

#define ANIM_MAX_VELOCITY 260.f
#define ANIM_TOPSPEED_WALK 100.f
#define ANIM_TOPSPEED_RUN 250.f
#define ANIM_TOPSPEED_RUN_CROUCH 85.f

#define ANIM_DEPLOY_RATELIMIT 0.15f

#define ANIM_POSE_PARAM_DELTA_DAMPEN 4.0f

#define ANIM_RELOAD_DURATION 0.75f

#define ANIM_MAX_DEPLOY_DELAY 1.f

ConVar mp_feetyawrate("mp_feetyawrate", "400", 0x2002, "How many degrees per second that we can turn our feet or upper body.");