#include "CEngineAPI.h"

#include "CEngine.h"

void CEngineAPI::SetEngineWindow(void* hWnd)
{
    if (g_pHammer)
    {
        g_pGame->InputDetachFromGameWindow();
        m_pEditorHwnd = hWnd;
        g_pVideoMode->SetGameWindow(m_pEditorHwnd);
    }
}

bool CEngineAPI::IsRunningSimulation()
{
    return g_pEngine->GetState() == 1;
}