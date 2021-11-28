#pragma once

#include "../mixed/mathlib.h"
#include "ConVar.h"

class VPlane;

ConVar r_occlusionspew("r_occlusionspew", "0", 0x4000, "Activate/deactivates spew about what the occlusion system is doing.");

#define OCCLUSION_SYSTEM_VIEWDATA_MAX 32

class COcclusionSystem
{
public:
	void SetView(const Vector& vecCameraPos, int flFov, const VMatrix& WorldToCamera, const VMatrix& CameraToProjection,
		const VPlane& NearClipPlane);

	int GetCurrentViewId();
	bool IsOccluded(int nOcclusionViewId, const Vector& vecAbsMins, const Vector& vecAbsMaxs);
	void SetOcclusionParameters(float flMaxOccluderArea, float flMinOccluderArea);
	float GetMinOccluderArea();

	struct ViewData_t
	{
		bool m_bEdgeListDirty;
		VMatrix m_WorldToProjection;
		VMatrix m_WorldToCamera;
		float m_flXProjScale;
		float m_flYProjScale;
		float m_flProjDistScale;
		float m_flProjDistOffset;
		Vector m_vecCameraPosition;
		cplane_t m_NearClipPlane;
		float m_flNearPlaneDist;
		float m_flFOVFactor;
	};

	int m_nCurrentViewId;
	ViewData_t m_ViewData[OCCLUSION_SYSTEM_VIEWDATA_MAX];
	char pad[500];
	float m_flMaxOccluderArea;
	float m_flMinOccluderArea;
	int m_nTests;
	int m_nOccluded;
};

inline COcclusionSystem* g_pOcclusionSystem;