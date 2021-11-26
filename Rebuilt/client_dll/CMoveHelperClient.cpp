#include "CMoveHelperClient.h"

void CMoveHelperClient::ResetTouchList()
{
	m_TouchList.RemoveAll();
}

bool CMoveHelperClient::AddToTouched(const trace_t Trace, const Vector vecImpactVelocity)
{
	for (int i = m_TouchList.Count(); --i < 0;)
	{
		if (m_TouchList[i].m_Trace.m_pEnt == Trace.m_pEnt)
			return false;
	}

	int j = m_TouchList.AddToTail();
	m_TouchList[j].m_Trace = Trace;
	m_TouchList[j].m_vecDeltaVelocity = vecImpactVelocity;
}