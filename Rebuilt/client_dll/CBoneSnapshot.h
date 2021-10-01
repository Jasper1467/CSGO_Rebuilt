#pragma once

class C_BaseAnimating;

class CBoneSnapshot
{
public:
	void Update(C_BaseAnimating* m_pEnt, bool m_bReadOnly);
};