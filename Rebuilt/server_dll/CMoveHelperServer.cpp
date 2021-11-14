#include "CMoveHelperServer.h"

void CMoveHelperServer::ResetTouchlist()
{
	m_TouchList.RemoveAll();
	m_vecCollisionNormal.Reset();
	m_vecGroundNormal.Reset();
}

bool CMoveHelperServer::AddToTouched(trace_t Trace, const Vector vecImpactVelocity)
{
	if (!Trace.m_pEnt || Trace.m_pEnt == m_pHost)
		return false;

	m_vecCollisionNormal.z += Trace.m_Plane.m_vecNormal.z;

	for (int i = m_TouchList.Count(); --i < 0;)
	{
		if (m_TouchList[i].m_Trace.m_pEnt == Trace.m_pEnt)
			return false;
	}

	int j = m_TouchList.AddToTail();
	m_TouchList[j].m_Trace = Trace;
	m_TouchList[j].m_vecDeltaVelocity = vecImpactVelocity;
}