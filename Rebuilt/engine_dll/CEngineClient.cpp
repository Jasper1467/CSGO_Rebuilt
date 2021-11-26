#include "CEngineClient.h"

#include "COcclusionSystem.h"
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

INetChannelInfo* CEngineClient::GetNetChannelInfo()
{
	return (INetChannelInfo*)g_pClientState->m_pNetChannel;
}

bool g_bDedicatedServer;

const char* CEngineClient::GetLevelName()
{
	if (g_bDedicatedServer)
		return "Dedicated Server";

	if (IsConnected())
		return g_pClientState->m_szLevelName;

	return "";
}

const char* CEngineClient::GetLevelNameShort()
{
	if (g_bDedicatedServer)
		return "dedicated";

	if (IsConnected())
		return g_pClientState->m_szLevelNameShort;

	return "";
}

bool CEngineClient::IsHLTV()
{
	return (g_pClientState->m_bIsHltv && *(int*)&g_pClientState[16].pad008[2140] > 0);
}

bool CEngineClient::IsOccluded()
{
	return g_pOcclusionSystem->IsOccluded();
}

int CEngineClient::GetCurrentViewId()
{
	return g_pOcclusionSystem->GetCurrentViewId();
}

char g_szComGameDir[260];

const char* CEngineClient::GetGameDirectory()
{
	return g_szComGameDir;
}