#pragma once

#include "../mixed/SomeDefs.h"

class CEngineUniformRandomStream
{
public:
	float RandFloat(float flMin, float flMax)
	{
		return RandomFloat(flMin, flMax);
	}

	int RandInt(int nMin, int nMax)
	{
		return RandomInt(nMin, nMax);
	}

	int RandFloatExp(float flMin, int flMax, float flExponent)
	{
		return RandomFloatExp(flMin, flMax, flExponent);
	}
};

inline CEngineUniformRandomStream* g_pRandom;