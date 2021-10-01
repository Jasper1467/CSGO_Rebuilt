#pragma once
#include <cmath>

inline float Approach(float m_flTarget, float m_flValue, float m_flSpeed)
{
	float m_flDelta = m_flTarget - m_flValue;

	if (m_flDelta > m_flSpeed)
		m_flValue += m_flSpeed;
	else if (m_flDelta < -m_flSpeed)
		m_flValue -= m_flSpeed;
	else
		m_flValue = m_flTarget;

	return m_flValue;
}

inline float AngleNormalize(float m_flAngle)
{
	m_flAngle = fmod(m_flAngle, 360.0f);

	if (m_flAngle > 180.0f)
		m_flAngle -= 360.0f;

	if (m_flAngle < -180.0f)
		m_flAngle += 360.0f;

	return m_flAngle;
}