#pragma once

class ConCommandBase
{
public:
	int vtable;
	ConVar* m_pNext;
	bool m_bRegistered;
	const char* m_szName;
	const char* m_szHelpString;
	int m_nFlags;
	char pad_0x0018[4];
};

class ConVar : ConCommandBase
{
public:
	ConVar(const char* szName, const char* szDefaultValue, int nFlags, const char* szExplanation)
	{
		// server.dll 55 8B EC 83 E4 F8 8B 45 0C 83 EC 10 F3 0F 10 45 1C
	}

	float GetFloat(); // 12
	int GetInt(); // 13

	ConVar* m_pParent;
	const char* m_szDefaultValue;
	char* m_szString;
	int m_nStringLength;
	float m_flValue;
	int m_nValue;
	bool m_bHasMin;
	float m_flMinVal;
	bool bHasMax;
	float m_flMaxVal;
	void* m_fnChangeCallback;
};