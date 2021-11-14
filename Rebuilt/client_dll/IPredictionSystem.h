#pragma once

#include "C_BaseEntity.h"

class IPredictionSystem
{
public:

	void SuppressEvents()
	{
		for (IPredictionSystem* pSys = m_pPredictionSystems; pSys; pSys = (IPredictionSystem*)pSys->m_pSuppressHost)
			pSys->m_bSuppressEvent = false;
	}

	static IPredictionSystem* m_pPredictionSystems;

	IPredictionSystem* m_pNextSystem;
	C_BaseEntity* m_pSuppressHost;
	bool m_bSuppressEvent;
	int m_nStatusPushed;
};