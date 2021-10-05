#include "CNetChan.h"

#define CONNECTION_PROBLEM_TIME 4.0f

bool CNetChan::IsTimingOut()
{
	
}

void CNetChan::SetChoked()
{
	m_nOutSequenceNr++;
	m_nChokedPackets++;
}