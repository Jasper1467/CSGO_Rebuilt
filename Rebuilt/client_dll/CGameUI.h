#pragma once
#include "../engine_dll/CEngineVGui.h"

// Interfaces set in CGameUI::Connect
void* g_pGameClientExports;
void* g_pPanoramaUIEngineExports;
void* g_pAchievementMgr;

enum GameUIFailureReason_e
{
	STEAMLOGINFAILURE_NOSTEAMLOGIN = 0x2,
	STEAMLOGINFAILURE_VACBANNED = 0x3,
	STEAMLOGINFAILURE_LOGGED_IN_ELSEWHERE = 0x4,
};

class CGameUI
{
public:
	void Connect(CreateInterfaceFn fnFactory);

	CreateInterfaceFn m_GameFactory;
	bool m_bTryingToLoadFriends;
	bool m_bActivatedUI;
	bool m_bHasSavedThisMenuSession;
	bool m_bOpenProgressOnStart;
	int m_nGameIP;
	int m_nGameConnectionPort;
	int m_nGameQueryPort;
	int m_nFriendsLoadPauseFrames;
	int m_nPlayGameStartupSound;
	char m_szPreviousStatusText[128];
	char m_szPlatformDir[260];
	char pad[90];
	bool m_bInitializePanoramaUI;
};