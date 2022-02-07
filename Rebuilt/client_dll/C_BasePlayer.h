#pragma once

#include "../mixed/Vectors.h"
#include "C_BaseEntity.h"

class C_BaseCombatWeapon
{
public:
};

class CWeaponCSBase
{
public:
	int GetCSZoomLevel(); // 442
	int GetZoomLevels(); // 443
};

ConVar sv_maxspeed = ConVar("sv_maxspeed", "450", 0x82100, "");

class C_BasePlayer : public C_BaseEntity
{
public:
	int GetPlayerState(); // 294
	bool IsAlive(); // 158
	C_BaseCombatWeapon* GetActiveWeapon();
	float GetPlayerMaxSpeed(); // 276
	void GetPredictionErrorSmoothingVector(Vector vecOffset);
	void CalcViewBob(Vector& vecEyeOrigin);
	void SetPlayerUnderwater(bool bState);

	const char* GetPlayerModelName()
	{
		return "models/player.mdl";
	}

	bool IsAlive()
	{
		return m_lifeState == 0;
	}

	float GetPlayerMaxSpeed();

	void NotePredictionError(Vector& vecDelta);

	int m_iHealth; // this + 0x100
	int m_fFlags; // this + 0x104
	Vector m_vecViewOffset; // this + 0x108
	Vector m_vecVelocity; // this + 0x114
	float m_flFriction; // this + 0x144
	int m_nNextThinkTick; // this + 0xFC
	int m_lifeState; // this + 0x25F
	int m_MoveType; // this + 0x25C
	float m_flWaterJumpTime; // this + 0x321
	Vector m_vecPredictionError; // this + 0xD6A
	float m_flPredictionErrorTime; // this + 0xD6D
	float m_flDuckAmount; // this + 0x2FBC
	float m_flDuckSpeed; // this + 0x2FC0
	bool m_bDucked; // this + 0x3054
	bool m_bDucking; // this + 0x3055
	float m_flLastDuckTime; // this + 0x3058
	bool m_bInDuckJump; // this + 0x305C
	int m_nDuckTimeMsecs; // this + 0x3018
	int m_nDuckJumpTimeMsecs; // this + 0x301C
	int m_nJumpTimeMsecs; // this + 0x3020
	float m_flFallVelocity; // this + 0x3024
	QAngle m_viewPunchAngle; // this + 0x3030
	QAngle m_aimPunchAngle; // this + 0x303C
	QAngle m_aimPunchAngleVel; // this + 0x3048
	bool m_bDrawViewmodel; // this + 0x305D
	bool m_bWearingSuit; // this + 0x305E
	int m_afButtonLast; // this + 0x31fC
	int m_afButtonPressed; // this + 0x3200
	int m_afButtonReleased; // this + 0x3204
	int m_nImpulse; // this + 0x320C
	int m_nButtons; // this + 0x3208
	bool m_bHasWalkMovedSinceLastJump; // this + 0x3228
	int m_vphysicsCollisionState; // this + 0x326C
	float m_surfaceFriction; // this + 0x323C
	float m_flMaxspeed; // this + 0x3258
	int m_iDefaultFOV; // this + 0x333C
	int m_iObserverMode; // this + 0x3388
	void* m_hViewEntity; // this + 0x334C
	int m_nTickBase; // this + 0x3440
	float m_flLaggedMovementValue; // this + 0x35A4
	char m_szLastPlaceName[18]; // this + 0x35C4
	Vector m_vecHack_RecvProxy_LocalPlayerOriginX; // this +0x3800
	float m_flOldFallVelocity; // this + 0x3028
	bool m_bInLanding; // this + 0x3061
	float m_flLandingTime; // this + 0x3064
	bool m_bPlayerUnderwater; // this + 0x358C
	float m_flPredictionErrorTime; // this + 0x35B4
	Vector m_vecPredictionError; // this + 0x35A8
};

inline C_BasePlayer* g_pLocalPlayer;