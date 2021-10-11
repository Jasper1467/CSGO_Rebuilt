#include "CEngineClient.h"

#include "CClientState.h"

int CEngineClient::GetMaxClients()
{
	return g_pClientState->m_nMaxClients;
}

bool CEngineClient::IsInGame()
{
	return g_pClientState->m_nSignonState == SIGNONSTATE_FULL;
}

bool CEngineClient::IsConnected()
{
	return g_pClientState->m_nSignonState >= SIGNONSTATE_CONNECTED;
}

INetChannel* CEngineClient::GetNetChannel()
{
	return g_pClientState->m_pNetChannel;
}

const char* CEngineClient::GetLevelName()
{
	if (byte_107A6D80)
		return "Dedicated Server";

	if (IsConnected())
		return g_pClientState->m_szLevelName;

	return "";
}

const char* CEngineClient::GetLevelNameShort()
{
	if (byte_107A6D80)
		return "dedicated";

	if (IsConnected())
		return g_pClientState->m_szLevelNameShort;

	return "";
}

bool CEngineClient::IsHLTV()
{
	return (g_pClientState->m_bIsHltv && *(int*)&g_pClientState[16].pad008[2140] > 0);
}