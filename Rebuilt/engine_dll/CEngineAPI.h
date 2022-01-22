#pragma once

struct StartupInfo_t
{
	void* m_pInstance;
	const char* m_szBaseDirectory;
	void* m_pInitialMod;
	const char* m_szInitialGame;
	void* m_pParentAppSystemGroup;
	bool m_bTextMode;
};

class CEngineAPI
{
public:


	void* m_pEditorHwnd;
	bool m_bRunningSimulation;
	StartupInfo_t m_StartupInfo;
};