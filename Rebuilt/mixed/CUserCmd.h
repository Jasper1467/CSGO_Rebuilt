#pragma once
#include "Vectors.h"

enum CUserCmd_Buttons_t
{
	IN_ATTACK = 0x1,
	IN_JUMP = 0x2,
	IN_DUCK = 0x4,
	IN_FORWARD = 0x8,
	IN_BACK = 0x10,
	IN_USE = 0x20,
	IN_CANCEL = 0x40,
	IN_LEFT = 0x80,
	IN_RIGHT = 0x100,
	IN_MOVELEFT = 0x200,
	IN_MOVERIGHT = 0x400,
	IN_ATTACK2 = 0x800,
	IN_RUN = 0x1000,
	IN_RELOAD = 0x2000,
	IN_ALT1 = 0x4000,
	IN_ALT2 = 0x8000,
	IN_SCORE = 0x10000,
	IN_SPEED = 0x20000,
	IN_WALK = 0x40000,
	IN_ZOOM = 0x80000,
	IN_WEAPON1 = 0x100000,
	IN_WEAPON2 = 0x200000,
	IN_BULLRUSH = 0x400000,
	IN_GRENADE1 = 0x800000,
	IN_GRENADE2 = 0x1000000,
	IN_LOOKSPIN = 0x2000000,
};

struct CUserCmd
{
	unsigned __int8 vtable;
	int m_nCommandNumber;
	int m_nTickCount;
	QAngle m_angViewAngles;
	Vector m_vecAimDirection;
	float m_flForwardMove;
	float m_flSideMove;
	float m_flUpMove;
	int m_nButtons;
	uint8_t m_uImpulse;
	int m_nWeaponSelect;
	int m_nWeaponSubType;
	int m_nRandomSeed;
	__int16 m_nMousedX;
	__int16 m_nMousedY;
	bool m_bHasBeenPredicted;
	QAngle m_angHeadAngles;
	Vector m_vecHeadOffset;
};