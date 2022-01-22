#include "COcclusionSystem.h"
#include "../mixed/SomeDefs.h"

void COcclusionSystem::SetView(const Vector& vecCameraPos, int flFov, const VMatrix& WorldToCamera,
    const VMatrix& CameraToProjection, const VPlane& NearClipPlane)
{
    m_nCurrentViewId = (m_nCurrentViewId + 1) % OCCLUSION_SYSTEM_VIEWDATA_MAX;
    ViewData_t* pActiveView = &m_ViewData[m_nCurrentViewId];

    pActiveView->m_vecCameraPosition = vecCameraPos;
    pActiveView->m_WorldToCamera = WorldToCamera;

    pActiveView->m_flXProjScale = -(CameraToProjection.m[2][3] / CameraToProjection.m[0][0]);
    pActiveView->m_flYProjScale = -(CameraToProjection.m[2][3] / CameraToProjection.m[1][1]);

    pActiveView->m_flProjDistScale = -CameraToProjection.m[2][3];
    pActiveView->m_flProjDistOffset = -CameraToProjection.m[2][2];

    MatrixMultiply(WorldToCamera.As3x4(), CameraToProjection.As3x4(), pActiveView->m_WorldToProjection.As3x4());

    pActiveView->m_NearClipPlane.m_vecNormal = NearClipPlane.m_vecNormal;
    pActiveView->m_NearClipPlane.m_nType = 3;
    pActiveView->m_bEdgeListDirty = true;
    pActiveView->m_flNearPlaneDist = std::max(pActiveView->m_flNearPlaneDist, 0.f);

    pActiveView->m_flFOVFactor = pActiveView->m_flNearPlaneDist * tan(flFov * 0.5f * M_PI / 180.0f);
    pActiveView->m_flFOVFactor = pActiveView->m_flNearPlaneDist / pActiveView->m_flFOVFactor;
    pActiveView->m_flFOVFactor *= pActiveView->m_flFOVFactor;

    if (&r_occlusionspew)
    {
        if (m_nTests)
        {
            Msg("Occl %.2f (%d/%d)\n", ((m_nOccluded / m_nTests) * 100.f, m_nOccluded, m_nTests));
            m_nTests = 0;
            m_nOccluded = 0;
        }
    }
}

int COcclusionSystem::GetCurrentViewId()
{
    return m_nCurrentViewId;
}

void COcclusionSystem::SetOcclusionParameters(float flMaxOccluderArea, float flMinOccluderArea)
{
    float v3 = flMaxOccluderArea;
    if (flMaxOccluderArea == 0.0)
        v3 = 5.0;

    m_flMaxOccluderArea = v3 * 0.001f;

    if (flMinOccluderArea == 0.0)
        m_flMinOccluderArea = 5.0;
    else
        m_flMinOccluderArea = flMinOccluderArea;
}

float COcclusionSystem::GetMinOccluderArea()
{
    return m_flMinOccluderArea;
}