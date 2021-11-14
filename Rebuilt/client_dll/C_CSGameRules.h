#pragma once

#include "../mixed/Vectors.h"

class C_CSGameRules
{
public:
	CViewVectors* GetViewVectors();
};

// As interface
inline C_CSGameRules* g_pGameRules;