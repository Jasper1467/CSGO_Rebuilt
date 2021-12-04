#pragma once

class C_GameInstructor
{
public:

	char pad[72];
	bool m_bNoDraw;
	char pad1[152];
	float m_flNextStartSoundTime;
	int m_nSplitScreenSlot;
	bool m_bHasLoadedSaveData;
	bool m_bEnsureThatInitIsNotCalledMultipleTimes;
};