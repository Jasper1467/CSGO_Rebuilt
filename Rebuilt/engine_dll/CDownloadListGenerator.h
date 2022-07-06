#pragma once

enum ConsistencyType_e
{
	CONSISTENCY_EXACT = 0x1,
	CONSISTENCY_SIMPLE_MATERIAL = 0x2,
};

typedef void* FileHandle_t;

class INetworkStringTable;

class CDownloadListGenerator
{
public:

	char pad[512];
	FileHandle_t m_hReslistFile;
	char pad2[52];
	INetworkStringTable* m_pStringTable;
};