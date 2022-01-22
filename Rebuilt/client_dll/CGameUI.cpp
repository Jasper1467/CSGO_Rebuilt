#include "CGameUI.h"
#include "../engine_dll/CEngineClient.h"
#include "../mixed/SomeDefs.h"

void CGameUI::Connect(CreateInterfaceFn fnFactory)
{
    g_pGameClientExports = fnFactory("GameClientExports001", 0);

    if (m_bInitializePanoramaUI)
        g_pPanoramaUIEngineExports = fnFactory("PanoramaUIEngine001", 0);

    g_pAchievementMgr = g_pEngineClient->GetAchievementMgr();
    Error("CGameUI::Initialize() failed to get necessary interfaces\n");

    m_GameFactory = fnFactory;
}