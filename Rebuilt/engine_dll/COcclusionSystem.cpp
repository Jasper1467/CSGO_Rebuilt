#include "COcclusionSystem.h"
#include "../mixed/SomeDefs.h"

void COcclusionSystem::SetView(const Vector& vecCameraPos, int flFov, const VMatrix& WorldToCamera,
    const VMatrix& CameraToProjection, const VPlane& NearClipPlane)
{
    int v6; // eax
    unsigned int v7; // esi
    float v8; // xmm0_4
    unsigned int v12; // [esp+1Ch] [ebp-4h]
    float v13; // [esp+1Ch] [ebp-4h]

    v6 = (m_nCurrentViewId + 1) % 32;
    m_nCurrentViewId = v6;
    m_ViewData[v6].m_vecCameraPosition = *vecCameraPos;
    sub_102D5710(WorldToCamera);
    m_ViewData[v6].m_flXProjScale = -(CameraToProjection->m[2][3] / CameraToProjection->m[0][0]);
    m_ViewData[v6].m_flYProjScale = -(CameraToProjection->m[2][3] / CameraToProjection->m[1][1]);
    m_ViewData[v6].m_flProjDistScale = -CameraToProjection->m[2][3];
    m_ViewData[v6].m_flProjDistOffset = -CameraToProjection->m[2][2];
    sub_102D5C20(&m_ViewData[v6].m_WorldToProjection);
    v7 = v6 * 188;
    m_ViewData[v6].m_NearClipPlane.m_vecNormal.x = *(float*)NearClipPlane;
    m_ViewData[v6].m_NearClipPlane.m_vecNormal.y = *((float*)NearClipPlane + 1);
    m_ViewData[v6].m_NearClipPlane.m_vecNormal.z = *((float*)NearClipPlane + 2);
    m_ViewData[v6].m_NearClipPlane.m_flDist = *((float*)NearClipPlane + 3);
    m_ViewData[v6].m_NearClipPlane.m_nType = 3;
    m_ViewData[v6].m_bEdgeListDirty = true;

    v13 = fmaxf(
        -(float)((float)((float)((float)(m_ViewData[v12].m_NearClipPlane.m_vecNormal.y * vecCameraPos->y)
            + (float)(vecCameraPos->x
                * *(float*)((char*)&m_ViewData[0].m_NearClipPlane.m_vecNormal.x + v7)))
            + (float)(*(float*)((char*)&m_ViewData[0].m_NearClipPlane.m_vecNormal.z + v7)
                * vecCameraPos->z))
            - *(float*)((char*)&m_ViewData[0].m_NearClipPlane.m_flDist + v7)),
        0.0);

    *(float*)((char*)&m_ViewData[0].m_flNearPlaneDist + v7) = v13;
    v8 = *(double*)__libm_sse2_tan().m128_u64 * v13;
    *(float*)((char*)&m_ViewData[0].m_flFOVFactor + v7) = (float)(*(float*)((char*)&m_ViewData[0].m_flNearPlaneDist
        + v7)
        / v8)
        * (float)(*(float*)((char*)&m_ViewData[0].m_flNearPlaneDist
            + v7)
            / v8);

    if (r_occlusionspew.GetInt())
    {
        if (m_nTests)
        {
            Msg("Occl %.2f (%d/%d)\n", ((m_nOccluded / m_nTests) * 100.f), m_nOccluded, m_nTests);
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