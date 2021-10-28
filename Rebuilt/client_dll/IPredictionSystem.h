#pragma once

#include "C_BaseEntity.h"

class IPredictionSystem
{
public:

	void SuppressEvents()
	{
		for (IPredictionSystem* pSys = s_pPredictionSystems; pSys; pSys = (IPredictionSystem*)pSys->m_pSuppressHost)
			pSys->m_bSuppressEvent = false;
	}

	// TODO: Is this actually in this class
	static IPredictionSystem* s_pPredictionSystems;

	IPredictionSystem* m_pNextSystem;
	C_BaseEntity* m_pSuppressHost;
	bool m_bSuppressEvent;
	int m_nStatusPushed;
};