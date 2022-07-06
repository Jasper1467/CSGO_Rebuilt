#include "CNetChan.h"
#include <math.h>
#include "../mixed/SomeDefs.h"

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

	if (m_flTimeOut == -1)
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

	m_flTimeOut = flSeconds;

	if (bForceExact)
		return;

	if (flSeconds <= 3600.f)
	{
		if (flSeconds > 0.f)
		{
			if (flSeconds < CONNECTION_PROBLEM_TIME)
				m_flTimeOut = CONNECTION_PROBLEM_TIME;
		}
		else
			m_flTimeOut = -1.f;
	}
	else
		m_flTimeOut = 3600.f;
}

void CNetChan::SetChoked()
{
	// FF 41 18 FF 41 2C

	m_nOutSequenceNr++;
	m_nChokedPackets++;
}

void CNetChan::GetSequenceData(int& nOutSequenceNr, int& nInSequenceNr, int& nOutSequenceNrAck)
{
	// 55 8B EC 8B 45 08 8B 51 18

	nOutSequenceNr = m_nOutSequenceNr;
	nInSequenceNr = m_nInSequenceNr;
	nOutSequenceNrAck = m_nOutSequenceNrAck;
}

//////////

void CNetChanParanoidMode::MessageItem_t::Dump()
{
	// [actual address in first opcode] E8 ? ? ? ? 46 81 C3 38 01 00 00

	if (this->m_pMsg && this->m_nEndBit == -1)
		Msg("---> DIDN'T FINISH PARSING %s\n", this->m_szName);

	Msg("%s: type( %d ) group ( %d ) size ( %d bytes ), startbit %d end bit %d\n",
		m_szName,
		m_nType,
		m_nGroup,
		m_nMessageSize,
		m_nStartBit,
		m_nEndBit);

	Msg("   %s\n", m_szDesc);

	if (m_pMsg)
	{
		Msg("RAW(%s) start\n", m_szName);
		LogMultiline(m_szName, (const char*)m_pMsg, m_nMessageSize);
		Msg("RAW(%s) end\n", m_szName);
	}
	else
	{
		Msg(" %s Control message\n", m_szName);
	}
}