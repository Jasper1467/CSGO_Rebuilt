#pragma once

class C_BaseAnimating;

class CBoneSnapshot
{
public:
	void Update(C_BaseAnimating* pEnt, bool bReadOnly);
};