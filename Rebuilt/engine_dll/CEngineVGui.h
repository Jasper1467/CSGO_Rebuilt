#pragma once

typedef void* (__cdecl* CreateInterfaceFn)(const char* szName, int* pReturnCode);

class CSysModule;
class CStaticPanel;
class CEnginePanel;
class CDebugSystemPanel;
class CFocusOverlayPanel;
class CTransitionEffectPanel;
class IMaterial;

typedef struct InputContextHandle_t__* InputContextHandle_t;

enum VGuiPanel_t
{
	PANEL_ROOT = 0x1,
	PANEL_CLIENTDLL = 0x2,
	PANEL_GAMEUIDLL = 0x3,
	PANEL_TOOLS = 0x4,
	PANEL_GAMEDLL = 0x5,
	PANEL_CLIENTDLL_TOOLS = 0x6,
	PANEL_GAMEUIBACKGROUND = 0x7,
	PANEL_TRANSITIONEFFECT = 0x8,
	PANEL_STEAMOVERLAY = 0x9,
};
namespace vgui
{
	typedef unsigned int VPANEL;

	class Panel
	{
	public:
		VPANEL GetVPanel();
	};

	typedef unsigned long HPanel;
	typedef int HContext;
	typedef unsigned long HFont;

	enum
	{
		DEFAULT_VGUI_CONTEXT = ((vgui::HContext)~0)
	};
}

class CEngineVGui
{
public:
	vgui::VPANEL GetPanel(int nType);

	vgui::Panel* GetRootPanel(int nType);

	bool IsInitialized()
	{
		return m_pStaticPanel != 0;
	}

	CreateInterfaceFn m_FactoryList[5];
	int m_nNumFactories;
	CSysModule* m_hStaticGameUIModule;
	CreateInterfaceFn m_GameUIFactory;
	CStaticPanel* m_pStaticPanel;
	CEnginePanel* m_pStaticClientDLLPanel;
	CEnginePanel* m_pStaticClientDLLToolsPanel;
	CEnginePanel* m_pStaticGameUIPanel;
	CEnginePanel* m_pStaticGameUIBackgroundPanel;
	CEnginePanel* m_pStaticGameDLLPanel;
	CEnginePanel* m_pStaticEngineToolsPanel;
	CDebugSystemPanel* m_pStaticDebugSystemPanel;
	CEnginePanel* m_pStaticSteamOverlayPanel;
	CFocusOverlayPanel* m_pStaticFocusOverlayPanel;
	CTransitionEffectPanel* m_pStaticTransitionPanel;
	char pad[8];
	bool m_bShowProgressDialog;
	char pad1[3];
	int m_nLastProgressPoint;
	int m_nLastProgressPointRepeatCount;
	char pad2[4];
	float m_flLoadingStartTime;
	char pad3[32];
	float m_flProgressBias;
	InputContextHandle_t m_hGameUIInputContext;
	IMaterial* m_pConstantColorMaterial;
};