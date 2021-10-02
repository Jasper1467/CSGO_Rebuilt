#include "C_BaseAnimating.h"
#include "../mixed/StringStuff.h"

#include <assert.h>

int C_BaseAnimating::LookupBone(const char* m_szName)
{
	Assert(GetModelPtr());

	if (!GetModelPtr())
		return -1;

	int v4 = Studio_BoneIndexByName(GetModelPtr(), m_szName);
	if (v4 == -1)
	{
		if (V_stristr(m_szName, "weapon_bone"))
			v4 = Studio_BoneIndexByName(GetModelPtr(), "hand_R");
		else if (V_stristr(m_szName, "Bip01_Head"))
			v4 = Studio_BoneIndexByName(GetModelPtr(), "head_0");
		else if (V_stristr(m_szName, "L_Hand"))
			v4 = Studio_BoneIndexByName(GetModelPtr(), "hand_L");
		else if (V_stristr(m_szName, "R_Hand"))
			v4 = Studio_BoneIndexByName(GetModelPtr(), "hand_R");
	}

	return v4;
}

void* C_BaseAnimating::GetModelPtr()
{
	void* result; // eax

	if (!m_pModelPtr && (*(int(__thiscall**)(void*))(this[1] + 32))(this + 1))
		sub_101C87E0();

	result = m_pModelPtr;
	if (!result || !*result)
		result = 0;
	return result;
}