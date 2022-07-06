#pragma once

enum QuitState_e
{
	QUIT_NOTQUITTING = 0x0,
	QUIT_TODESKTOP = 0x1,
	QUIT_RESTART = 0x2,
};

class CEngine
{
public:
	enum EngineState_e
	{
		DLL_INACTIVE = 0x0,
		DLL_ACTIVE = 0x1,
		DLL_CLOSE = 0x2,
		DLL_RESTART = 0x3,
		DLL_PAUSED = 0x4,
	};

	CEngine(void) {} // 1

	bool Load(bool bDedicated, const char* szRootDir); // 2
	void Unload() // 3
	{
		sub_10280BF0();

		m_nCurrentState = 0;
		m_nNextState = 0;
	}

	void SetNextState(int nNextState) // 4
	{
		m_nNextState = nNextState;
	}

	int GetState() // 5
	{
		return m_nCurrentState;
	}

	void Frame(); // 6

	float GetFrameTime() // 7
	{
		return m_flFrameTime;
	}

	float GetCurTime() // 8
	{
		return m_flCurTime;
	}

	int GetQuitState() // 9
	{
		return m_nQuitState;
	}

	void SetQuitState(int nQuitState) // 10
	{
		m_nQuitState = nQuitState;
	}

	int m_nQuitState;
	int m_nCurrentState;
	int m_nNextState;
	float m_flCurTime;
	char pad1[4];
	float m_flFrameTime;
};

inline CEngine* g_pEngine; // As interface