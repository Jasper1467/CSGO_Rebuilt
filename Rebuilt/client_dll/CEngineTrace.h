#pragma once

#include "../engine_dll/CEngineTrace.h"

struct trace_t
{
	Vector m_vecStartPos;
	Vector m_vecEndPos;
	cplane_t m_Plane;
	float m_flFraction;
	int m_nContents;
	unsigned __int16 m_nDispFlags;
	bool m_bAllSolid;
	bool m_bStartSolid;
	float m_flFractionLeftSolid;
	csurface_t m_Surface;
	int m_nHitGroup;
	__int16 m_nPhysicsBone;
	unsigned __int16 m_nWorldSurfaceIndex;
	C_BaseEntity* m_pEnt;
	int m_nHitBox;
};