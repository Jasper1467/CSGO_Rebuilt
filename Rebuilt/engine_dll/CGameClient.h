#pragma once

struct CClientFrame
{
	char pad[8];
	int m_nTickCount;
};

class CGameClient
{
public:

	
	char pad[1092];
	bool m_bVoiceLoopback;
	char pad1[67];
	int m_nLastMovementTick;
	int m_nSoundSequence;
	void* m_pEdict;
	char pad2[24];
	CClientFrame* m_pCurrentFrame;
};