#pragma once
#include "C_BaseEntity.h"
#include "../mixed/Vectors.h"
#include "../mixed/CUtlVector.h"
#include "CEngineTrace.h"

class CMoveHelperClient
{
public:
	void ResetTouchList();
	bool AddToTouched(const trace_t Trace, const Vector vecImpactVelocity);

	struct TouchList_t
	{
		Vector m_vecDeltaVelocity;
		trace_t m_Trace;
	};

	CUtlVector<TouchList_t> m_TouchList;
	C_BaseEntity* m_pHost;
};