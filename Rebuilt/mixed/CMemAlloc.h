#pragma once

#include <cstdint>

using MemAllocFailHandler_t = size_t(__cdecl*)(size_t);

class CMemAlloc
{
public:
	// Release versions
	void* Alloc(size_t nSize);
	void* Realloc(void* pMemory, size_t nSize);
	void Free(void* pMemory);
	void* Expand_NoLongerSupported(void* pMemory, size_t nSize);

	// Debug versions
	void* Alloc(size_t nSize, const char* szFileName, int nLine);
	void* Realloc(void* pMemory, size_t nSize, const char* szFileName, int nLine);
	void Free(void* pMemory, const char* szFileName, int nLine);
	void* Expand_NoLongerSupported(void* pMemory, size_t nSize, const char* szFileName, int nLine);
};

// As interface
CMemAlloc* g_pMemAlloc;