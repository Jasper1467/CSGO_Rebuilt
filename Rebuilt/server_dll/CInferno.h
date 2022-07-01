#pragma once

#include "../mixed/Vectors.h"

class CountdownTimer
{
public:
	void Invalidate()
	{
		m_flTimeStamp = -1.f;
	}

	float m_flDuration;
	float m_flTimeStamp;
};

struct Extent
{
	Vector lo;
	Vector hi;
};

class CInferno
{
public:
	struct FireInfo_t
	{
		Vector m_vecPos;
		char pad[72];
		CountdownTimer m_LifeTime;
	};

	char pad[2524];
	int m_fireCount;
	char pad1[12];
	CInferno::FireInfo_t* m_pFire[64];
	Extent m_extent;
	char pad3[24];
	Vector m_splashVelocity;
	Vector m_startPos;
	char pad4[28];
	CountdownTimer m_BookkeepingTimer;
};