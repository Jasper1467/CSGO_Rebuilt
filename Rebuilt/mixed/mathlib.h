#pragma once
#include <cmath>

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