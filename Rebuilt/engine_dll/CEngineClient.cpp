#include "CEngineClient.h"

#include "CClientState.h"

int CEngineClient::GetMaxClients()
{
	return g_pClientState->m_nMaxClients;
}