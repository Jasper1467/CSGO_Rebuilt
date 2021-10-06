#pragma once

class studiohdr_t
{
public:

};

class virtualmodel_t
{
public:

};

struct CStudioHdr
{
	studiohdr_t* m_pStudioHdr;
	virtualmodel_t* m_pVModel;
	void* m_pStudioHdrCache;
	int m_nFrameUnlockCounter;
	int* m_pFrameUnlockCounter;
	void* m_FrameUnlockCounterMutex;
	char pad0[4];
	void* m_boneFlags;
	void* m_boneParent;
};