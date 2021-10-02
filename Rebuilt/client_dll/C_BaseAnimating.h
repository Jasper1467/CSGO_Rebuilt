#pragma once

class C_BaseAnimating
{
public:
	int LookupBone(const char* m_szName);
	void* GetModelPtr();

	void* m_pModelPtr; // this[2644]
};