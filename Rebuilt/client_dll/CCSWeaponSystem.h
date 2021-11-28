#pragma once

class CCSWeaponSystem
{
public:
	const char* GetName()
	{
		const char* v1 = m_szName;
		const char* result = "unnamed";
		if (v1)
			result = v1;

		return result;
	}

	char pad[4];
	const char* m_szName;
};