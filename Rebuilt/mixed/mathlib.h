#pragma once
#include <cmath>

#include "Vectors.h"

#define M_PI 3.14159265358979323846
#define RAD2DEG( x  )  ( (float)(x) * (float)(180.f / M_PI_F) )
#define DEG2RAD( x  )  ( (float)(x) * (float)(M_PI_F / 180.f) )

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

inline void MatrixMultiply(const matrix3x4_t& a1, const matrix3x4_t& a2, const matrix3x4_t& a3)
{
	// Why do i suck at math so much :(
}