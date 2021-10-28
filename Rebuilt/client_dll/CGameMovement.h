#pragma once
#include "../mixed/Vectors.h"
#include "C_BasePlayer.h"
#include "C_CSPlayer.h"
#include "../engine_dll/ConVar.h"

#define GAMEMOV_PLAYER_MAX_SAFE_FALL_SPEED 580.f
#define GAMEMOV_IN_SPEED_MULTIPLIER 0.5f

struct CMoveData
{
	bool m_bFirstRunOfFunctions;
	bool m_bGameCodeMovedPlayer;
	bool m_bNoAirControl;
	uintptr_t m_hPlayerHandle;
	int m_nImpulseCommand;
	QAngle m_angViewAngles;
	QAngle m_angAbsViewAngles;
	int m_nButtons;
	int m_nOldButtons;
	float m_flForwardMove;
	float m_flSideMove;
	float m_flUpMove;
	float m_flMaxSpeed;
	float m_flClientMaxSpeed;
	Vector m_vecVelocity;
	Vector m_vecTrailingVelocity;
	float m_flTrailingVelocityTime;
	Vector m_vecAngles;
	Vector m_vecOldAngles;
	float m_flOutStepHeight;
	Vector m_vecOutWishVel;
	Vector m_vecOutJumpVel;
	Vector m_vecConstraintCenter;
	float m_flConstraintRadius;
	float m_flConstraintWidth;
	float m_flConstraintSpeedFactor;
	bool m_bConstraintPastRadius;
	Vector m_vecAbsOrigin;
};

enum SpeedCropped_t
{
	SPEED_CROPPED_RESET = 0x0,
	SPEED_CROPPED_DUCK = 0x1,
	SPEED_CROPPED_WEAPON = 0x2,
};

class CGameMovement
{
public:
	void ProcessMovement(C_BasePlayer* pPlayer, CMoveData* pMoveData);
	void Reset();
	void Log(const char* szFormat, ...);
	void PlayerMove();
	void ResetGetWaterContentsForPointCache();

	C_BasePlayer* m_pPlayer;
	CMoveData* m_pMoveData;
	int m_nOldWaterLevel;
	float m_flWaterEntryTime;
	int m_nOnLadder;
	Vector m_vecForward;
	Vector m_vecRight;
	Vector m_vecUp;
	int m_nCachedGetPointContents[64][3];
	Vector m_CachedGetPointContentsPoint[64][3];
	int m_nSpeedCropped;
	bool m_bProcessingMovement;
	bool m_bInStuckTest;
	float m_flStuckCheckTime[65][2];
	int* m_pTraceListData;
	int m_nTraceCount;
};

// TODO: correct these
ConVar sv_accelerate_use_weapon_speed("sv_accelerate_use_weapon_speed", "400", 0x82100, "");
ConVar sv_weapon_encumbrance_scale("sv_weapon_encumbrance_scale", "400", 0x82000, "");
ConVar healthshot_healthboost_speed_multiplier("healthshot_healthboost_speed_multiplier", "400", 0x82000, "");

class CCSGameMovement : public CGameMovement
{
public:
	bool CanAccelerate();
	void Accelerate(Vector& vecWishDir, float flWishSpeed, float flAcceleration);

	C_CSPlayer* m_pCSPlayer;
};