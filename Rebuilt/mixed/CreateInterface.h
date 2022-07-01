#pragma once
#include <string.h>

typedef void* (__cdecl* CreateInterfaceFn)(const char* szName, int* pReturnCode);
typedef void* (__cdecl* InstantiateInterfaceFn)();

struct InterfaceReg
{
	InstantiateInterfaceFn m_fnCreate;
	const char* m_szName;
	InterfaceReg* m_pNext;
};

enum InterfaceReturnCode_e
{
	IFACE_OK = 0x0,
	IFACE_FAILED = 0x1,
};

static InterfaceReg* s_pInterfaceRegs;

void* CreateInterfaceInternal(const char* szInterfaceName, int* pReturnCode)
{
	InterfaceReg* pCur;

	for (pCur = s_pInterfaceRegs; pCur; pCur = pCur->m_pNext)
	{
		if (strcmp(pCur->m_szName, szInterfaceName) == 0)
		{
			if (pReturnCode)
				*pReturnCode = IFACE_OK;

			return pCur->m_fnCreate();
		}
	}

	if (pReturnCode)
		*pReturnCode = IFACE_FAILED;

	return NULL;
}

void* CreateInterface(const char* szInterfaceName, int* pReturnCode)
{
	return CreateInterfaceInternal(szInterfaceName, pReturnCode);
}