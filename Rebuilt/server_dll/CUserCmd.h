#pragma once

#include "../mixed/CUserCmd.h"

class CUserCmd
{
public:
	~CUserCmd() {}

	CRC32_t GetChecksum();

	void Reset()
	{
		m_nCommandNumber = 0;
		m_nTickCount = 0;
		m_angViewAngles.Reset();
		m_vecAimDirection.Reset();
		m_flForwardMove = 0.f;
		m_flSideMove = 0.f;
		m_flUpMove = 0.f;
		m_nButtons = 0;
		m_nImpulse = 0;
		m_nWeaponSelect = 0;
		m_nWeaponSubType = 0;
		m_nRandomSeed = 0;
		m_nServerRandomSeed = 0;
		m_nMousedX = 0;
		m_nMousedY = 0;
		m_bHasBeenPredicted = false;
		m_angHeadAngles.Reset();
		m_vecHeadOffset.Reset();
	}

	int m_nCommandNumber;
	int m_nTickCount;
	QAngle m_angViewAngles;
	Vector m_vecAimDirection;
	float m_flForwardMove;
	float m_flSideMove;
	float m_flUpMove;
	int m_nButtons;
	uint8_t m_nImpulse;
	int m_nWeaponSelect;
	int m_nWeaponSubType;
	int m_nRandomSeed;
	int m_nServerRandomSeed;
	__int16 m_nMousedX;
	__int16 m_nMousedY;
	bool m_bHasBeenPredicted;
	QAngle m_angHeadAngles;
	Vector m_vecHeadOffset;
};