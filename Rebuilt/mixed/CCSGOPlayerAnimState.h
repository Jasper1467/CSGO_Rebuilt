#pragma once

#include "mathlib.h"

struct aimmatrix_transition_t
{
	float m_flDurationStateHasBeenValid;
	float m_flDurationStateHasBeenInValid;
	float m_flHowLongToWaitUntilTransitionCanBlendIn;
	float m_flHowLongToWaitUntilTransitionCanBlendOut;
	float m_flBlendValue;

	void UpdateTransitionState(float m_flTimeInterval, float m_flSpeed, bool m_bStateShouldBeValid)
	{
		if (m_bStateShouldBeValid)
		{
			m_flDurationStateHasBeenInValid = 0.f;
			m_flDurationStateHasBeenValid += m_flTimeInterval;

			if (m_flDurationStateHasBeenValid >= m_flHowLongToWaitUntilTransitionCanBlendIn)
				m_flBlendValue = Approach(1.f, m_flBlendValue, m_flSpeed);
		}
		else
		{
			m_flDurationStateHasBeenValid = 0.f;
			m_flDurationStateHasBeenInValid += m_flTimeInterval;

			if (m_flDurationStateHasBeenInValid >= m_flHowLongToWaitUntilTransitionCanBlendOut)
				m_flBlendValue = Approach(0.f, m_flBlendValue, m_flSpeed);
		}
	}
};

struct animstate_pose_param_cache_t
{
	bool m_bInitialized;
	char pad_01[3];
	int32_t m_iPoseParameter;
	char* m_szPoseParameter;
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