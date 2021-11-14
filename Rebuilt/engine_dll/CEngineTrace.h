#pragma once
#include "../mixed/Vectors.h"
#include "../client_dll/C_BaseEntity.h"

struct cplane_t
{
	Vector m_vecNormal;
	float m_flDist;
	unsigned __int8 m_nType;
	unsigned __int8 m_nSignBits;
	unsigned __int8 pad[2];
};

struct csurface_t
{
	const char* m_szName;
	__int16 m_nSurfaceProps;
	unsigned __int16 m_nFlags;
};