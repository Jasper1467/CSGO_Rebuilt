#include "CNetChan.h"

#define CONNECTION_PROBLEM_TIME 4.0f
#define TICK_INTERVAL 0.25f

bool CNetChan::IsTimingOut()
{
	if (m_flTimeout == -1)
		return false;

	return net_time > m_flLastReceived + CONNECTION_PROBLEM_TIME;
}

void CNetChan::SetChoked()
{
	m_nOutSequenceNr++;
	m_nChokedPackets++;
}

void CNetChan::SetTimeout(float m_flSeconds, bool m_bForceExact)
{
	m_flTimeout = m_flSeconds;

	if (m_bForceExact)
		return;

	if (m_flSeconds <= 3600.f)
	{
		if (m_flSeconds > 0.f)
		{
			if (m_flSeconds < CONNECTION_PROBLEM_TIME)
				m_flTimeout = CONNECTION_PROBLEM_TIME;
		}
		else
			m_flTimeout = -1.f;
	}
	else
		m_flTimeout = 3600.f;
}