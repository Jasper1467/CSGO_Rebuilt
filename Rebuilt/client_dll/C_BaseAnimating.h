#pragma once

#include "C_BaseEntity.h"

class C_BaseAnimating : public C_BaseEntity
{
public:
	int LookupBone(const char* m_szName);
	void* GetModelPtr();
	bool ShouldSkipAnimationFrame();
	bool IsPlayer(); // Index 158

	void* m_pModelPtr; // this[2644]
	int m_nLastNonSkippedFrame; // this[666]
};