#pragma once

#include "../mixed/mathlib.h"
#include "ConVar.h"

class VPlane;

ConVar r_occlusionspew("r_occlusionspew", "0", 0x4000, "Activate/deactivates spew about what the occlusion system is doing.");

class COcclusionSystem
{
public:
	void SetView(const Vector* vecCameraPos, int flFov, VMatrix* WorldToCamera, VMatrix* CameraToProjection, VPlane* NearClipPlane);
	int GetCurrentViewId();
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

	int vtable;
	int m_nCurrentViewId;
	ViewData_t m_ViewData[32];
	char pad[500];
	float m_flMaxOccluderArea;
	float m_flMinOccluderArea;
	int m_nTests;
	int m_nOccluded;
};