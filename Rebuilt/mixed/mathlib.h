#pragma once
#include <cmath>

#include "Vectors.h"

struct cplane_t
{
	Vector m_vecNormal;
	float m_flDist;
	unsigned __int8 m_nType;
	unsigned __int8 m_nSignBits;
	unsigned __int8 pad[2];
};

inline float Approach(float flTarget, float flValue, float flSpeed)
{
	float flDelta = flTarget - flValue;

	if (flDelta > flSpeed)
		flValue += flSpeed;
	else if (flDelta < -flSpeed)
		flValue -= flSpeed;
	else
		flValue = flTarget;

	return flValue;
}

inline float AngleNormalize(float flAngle)
{
	flAngle = fmod(flAngle, 360.0f);

	if (flAngle > 180.0f)
		flAngle -= 360.0f;

	if (flAngle < -180.0f)
		flAngle += 360.0f;

	return flAngle;
}

inline float DotProduct(const Vector& a, const Vector& b)
{
	return (a.x * b.x + a.y + b.y + a.z + b.z);
}