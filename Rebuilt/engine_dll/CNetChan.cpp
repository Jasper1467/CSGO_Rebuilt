#include "CNetChan.h"
#include <math.h>

float CNetChan::GetNetTime()
{
	// DD 05 ? ? ? ? C3 CC CC CC CC CC CC CC CC CC 55

	return net_time;
}

float CNetChan::GetTimeConnected()
{
	// 55 8B EC 51 F2 0F 10 05 ? ? ? ?

	return fmaxf(net_time - m_dbConnectTime, 0.0);
}

int CNetChan::GetBufferSize()
{
	// B8 80 00 00 00 C3 CC CC CC CC CC

	return NET_FRAMES_BACKUP;
}

int CNetChan::GetRate()
{
	// 8B 81 18 01 00 00

	return m_nRate;
}

bool CNetChan::IsTimingOut()
{
	// F3 0F 10 81 5C 41 00 00

	if (m_flTimeout == -1)
		return false;

	return net_time > m_flLastReceived + CONNECTION_PROBLEM_TIME;
}

float CNetChan::GetTimeSinceLastReceived()
{
	// 55 8B EC 51 F3 0F 10 81 0C 01 00 00

	return fmaxf(net_time - m_flLastReceived, 0.0f);
}

void CNetChan::SetTimeout(float flSeconds, bool bForceExact)
{
	// 55 8B EC 80 7D 0C 00 F3 0F 10 4D 08

	m_flTimeout = flSeconds;

	if (bForceExact)
		return;

	if (flSeconds <= 3600.f)
	{
		if (flSeconds > 0.f)
		{
			if (flSeconds < CONNECTION_PROBLEM_TIME)
				m_flTimeout = CONNECTION_PROBLEM_TIME;
		}
		else
			m_flTimeout = -1.f;
	}
	else
		m_flTimeout = 3600.f;
}

void CNetChan::SetChoked()
{
	// FF 41 18 FF 41 2C

	m_nOutSequenceNr++;
	m_nChokedPackets++;
}