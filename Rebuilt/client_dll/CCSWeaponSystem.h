#pragma once

class CCSWeaponSystem
{
public:
	const char* GetName()
	{
		return m_szName ? m_szName : "unnamed";
	}

	char pad[4];
	const char* m_szName;
};