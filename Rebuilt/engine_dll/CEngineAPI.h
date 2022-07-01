#pragma once
#include "CEngineVGui.h"

enum InitReturnVal_e
{
	INIT_FAILED = 0x0,
	INIT_OK = 0x1,
	INIT_LAST_VAL = 0x2,
};

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
	bool Connect(CreateInterfaceFn fnFactory); // 0
	void Disconnect(); // 1
	void* QueryInterface(const char* szInterfaceName); // 2
	InitReturnVal_e Init(); // 3

	bool SetStartupInfo(StartupInfo_t& Info); // 9
	int Run(); // 10
	void SetEngineWindow(void* hWnd); // 11
	void PostConsoleCommand(const char* szCommand); // 12
	bool IsRunningSimulation(); // 13
	bool ActivateSimulation(bool bActive); // 14
	void SetMap(const char* szMapName);

	void* m_pEditorHwnd;
	bool m_bRunningSimulation;
	StartupInfo_t m_StartupInfo;
};