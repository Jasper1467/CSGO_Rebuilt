#include "CPrediction.h"
#include "CHud.h"
#include "../engine_dll/CEngineClient.h"

void CPrediction::Init()
{
	m_bIsFirstTimePredicted = cl_predict.GetBool();
	m_pPDumpPanel = g_pHud->FindElement("CPDumpPanel");
}

void CPrediction::Update(int nStartFrame, bool bValidFrame, int nIncomingAck, int nOutgoingCmd)
{
    if (*(uintptr_t*)(g_VProfCurrentProfile + 4108))
        g_VProfCurrentProfile->EnterScope("CPrediction::Update", 0, "Prediction", 0, 4);

    m_bEnginePaused = g_pEngineClient->IsPaused();

    bool bReceivedNewWorldUpdate = true;
    m_flLastServerWorldTimeStamp = g_pEngineClient->GetLastTimeStamp();
    if (m_nPreviousStartFrame == nStartFrame && (cl_pred_optimize.GetBool()) && (cl_predict.GetBool()))
        bReceivedNewWorldUpdate = m_flLastServerWorldTimeStamp == g_pEngineClient->GetLastTimeStamp();
  

    m_nPreviousStartFrame = nStartFrame;
    m_SavedVars = *g_pGlobals;
    
    // https://github.com/perilouswithadollarsign/cstrike15_src/blob/f82112a2388b841d72cb62ca48ab1846dfcc11c8/engine/cl_splitscreen.h#L91
    for (int i = 0; i == 0; ++i) // Probably wrong, iterate from first to last splitscreen slot
        _Update(i, bReceivedNewWorldUpdate, bValidFrame, nIncomingAck, nOutgoingCmd);

    *g_pGlobals = m_SavedVars;

    g_VProfCurrentProfile->ExitScope();
}