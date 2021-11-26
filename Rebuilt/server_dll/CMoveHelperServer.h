#pragma once

#include "../mixed/Vectors.h"
#include "CEngineTrace.h"
#include "../mixed/CUtlVector.h"

class CBaseEntity;

class CMoveHelperServer
{
public:
	void ResetTouchlist();
	bool AddToTouched(trace_t Trace, const Vector vecImpactVelocity);

	struct TouchList_t
	{
		Vector m_vecDeltaVelocity;
		trace_t m_Trace;
	};

	CBaseEntity* m_pHost;
	CUtlVector<TouchList_t> m_TouchList;
	Vector m_vecCollisionNormal;
	Vector m_vecGroundNormal;
};