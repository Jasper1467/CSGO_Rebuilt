#include "CEngineVGui.h"
#include "CEngineClient.h"

vgui::VPANEL CEngineVGui::GetPanel(int nType)
{
    return GetRootPanel(nType)->GetVPanel();
}

vgui::Panel* CEngineVGui::GetRootPanel(int nType)
{
    vgui::Panel* result; // eax

    if (g_bDedicatedServer)
        return 0;

    switch (nType)
    {
    case PANEL_ROOT:
        result = (vgui::Panel*)m_pStaticGameUIPanel;
        break;
    case PANEL_CLIENTDLL:
        result = (vgui::Panel*)m_pStaticClientDLLPanel;
        break;
    case PANEL_GAMEUIDLL:
        result = (vgui::Panel*)m_pStaticEngineToolsPanel;
        break;
    case PANEL_GAMEDLL:
        result = (vgui::Panel*)m_pStaticGameDLLPanel;
        break;
    case PANEL_CLIENTDLL_TOOLS:
        result = (vgui::Panel*)m_pStaticClientDLLToolsPanel;
        break;
    case PANEL_GAMEUIBACKGROUND:
        result = (vgui::Panel*)m_pStaticGameUIBackgroundPanel;
        break;
    case PANEL_TRANSITIONEFFECT:
        result = (vgui::Panel*)m_pStaticFocusOverlayPanel;
        break;
    case PANEL_STEAMOVERLAY:
        result = (vgui::Panel*)m_pStaticDebugSystemPanel;
        break;
    default:
        result = (vgui::Panel*)m_pStaticPanel;
        break;
    }

    return result;
}