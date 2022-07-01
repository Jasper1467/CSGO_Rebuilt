#pragma once

#include "mathlib.h"
#include "../engine_dll/ConVar.h"

struct aimmatrix_transition_t
{
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

	float m_flDurationStateHasBeenValid;
	float m_flDurationStateHasBeenInValid;
	float m_flHowLongToWaitUntilTransitionCanBlendIn;
	float m_flHowLongToWaitUntilTransitionCanBlendOut;
	float m_flBlendValue;
};

struct animstate_pose_param_cache_t
{
	// client.dll [actual address in first opcode] E8 ? ? ? ? 8B 46 60 83 B8 9C 29 00 00 00 74 6D
	float GetValue(C_CSPlayer* pPlayer)
	{
		int v3; // esi
		double result; // st7

		if (!m_bInitialized && (Init(pPlayer, m_szName), !m_bInitialized))
			return result;

		if (!pPlayer)
			return result;

		(*(void(__thiscall**)(int))(*(_DWORD*)g_pMdlCache + 132))(g_pMdlCache);// BeginLock

		result = pPlayer->GetPoseParameter(m_nIndex);

		(*(void (__usercall**)(int@<ecx>, double@<st0>))(*(_DWORD*)g_pMdlCache + 136))(g_pMdlCache, result);// EndLock
		return result;
	}

	// client.dll [actual address in first opcode] E8 ? ? ? ? 80 BF B0 01 00 00 00
	bool Init(C_CSPlayer* pPlayer, const char* szName)
	{
		const char* v5 = szName;
		m_szName = szName;
		if (!pPlayer->GetModelPtr())
			v5 = szName;

		CStudioHdr* pModelPtr = pPlayer->m_pModelPtr;
		if (!pModelPtr)
			pModelPtr = 0;

		m_nIndex = pPlayer->LookupPoseParameter(pModelPtr, v5);
		if (m_nIndex != -1)
			m_bInitialized = true;

		(*(void(__thiscall**)(int))(*(_DWORD*)g_pMdlCache + 132))(g_pMdlCache);// BeginLock

		(*(void(__thiscall**)(int))(*(_DWORD*)g_pMdlCache + 136))(g_pMdlCache);// EndLock

		return m_bInitialized;
	}

	bool m_bInitialized;
	char pad[3];
	int m_nIndex;
	const char* m_szName;
};

enum AnimationLayer_e
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

enum AnimLayerFlag_e
{
	ANIM_LAYER_FLAG_ACTIVE = 0x1,
	ANIM_LAYER_FLAG_AUTOKILL = 0x2,
	ANIM_LAYER_FLAG_KILLME = 0x4,
	ANIM_LAYER_FLAG_DONTRESTORE = 0x8,
	ANIM_LAYER_FLAG_CHECKACCESS = 0x10,
	ANIM_LAYER_FLAG_DYING = 0x20,
	ANIM_LAYER_FLAG_NOEVENTS = 0x40,
};

enum LegAnimType_e
{
	LEGANIM_9WAY = 0x0,
	LEGANIM_8WAY = 0x1,
	LEGANIM_GOLDSRC = 0x2,
};

enum PlayerAnimEvent_e
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

enum AnimTag_e
{
	ANIMTAG_UNINITIALIZED = 0x0,
	ANIMTAG_STARTCYCLE_N = 0x1,
	ANIMTAG_STARTCYCLE_NE = 0x2,
	ANIMTAG_STARTCYCLE_E = 0x3,
	ANIMTAG_STARTCYCLE_SE = 0x4,
	ANIMTAG_STARTCYCLE_S = 0x5,
	ANIMTAG_STARTCYCLE_SW = 0x6,
	ANIMTAG_STARTCYCLE_W = 0x7,
	ANIMTAG_STARTCYCLE_NW = 0x8,
	ANIMTAG_AIMLIMIT_YAWMIN_IDLE = 0x9,
	ANIMTAG_AIMLIMIT_YAWMAX_IDLE = 0xA,
	ANIMTAG_AIMLIMIT_YAWMIN_WALK = 0xB,
	ANIMTAG_AIMLIMIT_YAWMAX_WALK = 0xC,
	ANIMTAG_AIMLIMIT_YAWMIN_RUN = 0xD,
	ANIMTAG_AIMLIMIT_YAWMAX_RUN = 0xE,
	ANIMTAG_AIMLIMIT_YAWMIN_CROUCHIDLE = 0xF,
	ANIMTAG_AIMLIMIT_YAWMAX_CROUCHIDLE = 0x10,
	ANIMTAG_AIMLIMIT_YAWMIN_CROUCHWALK = 0x11,
	ANIMTAG_AIMLIMIT_YAWMAX_CROUCHWALK = 0x12,
	ANIMTAG_AIMLIMIT_PITCHMIN_IDLE = 0x13,
	ANIMTAG_AIMLIMIT_PITCHMAX_IDLE = 0x14,
	ANIMTAG_AIMLIMIT_PITCHMIN_WALKRUN = 0x15,
	ANIMTAG_AIMLIMIT_PITCHMAX_WALKRUN = 0x16,
	ANIMTAG_AIMLIMIT_PITCHMIN_CROUCH = 0x17,
	ANIMTAG_AIMLIMIT_PITCHMAX_CROUCH = 0x18,
	ANIMTAG_AIMLIMIT_PITCHMIN_CROUCHWALK = 0x19,
	ANIMTAG_AIMLIMIT_PITCHMAX_CROUCHWALK = 0x1A,
	ANIMTAG_FLASHBANG_PASSABLE = 0x1B,
	ANIMTAG_WEAPON_POSTLAYER = 0x1C,
	ANIMTAG_MAX = 0x1D,
};

#define ANIM_MOVING_MINIMUM_SPEED 0.5f

#define ANIM_MAX_VELOCITY 260.f
#define ANIM_TOPSPEED_WALK 100.f
#define ANIM_TOPSPEED_RUN 250.f
#define ANIM_TOPSPEED_RUN_CROUCH 85.f

#define ANIM_DUCK_APPROACH_SPEED_UP 3.1f
#define ANIM_DUCK_APPROACH_SPEED_DOWN 6.f

#define ANIM_DEPLOY_RATELIMIT 0.15f

#define ANIM_POSE_PARAM_DELTA_DAMPEN 4.0f

#define ANIM_RELOAD_DURATION 0.75f

#define ANIM_MAX_DEPLOY_DELAY 1.f

ConVar mp_feetyawrate("mp_feetyawrate", "400", 0x2002, "How many degrees per second that we can turn our feet or upper body.");