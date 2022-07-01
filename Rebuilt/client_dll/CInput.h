#pragma once

#include "CUserCmd.h"
#include "../mixed/bitbuf.h"

#define MULTIPLAYER_BACKUP 150

struct kbutton_t
{
	struct Split_t
	{
		int m_nDown[2];
		int m_nState;
	};

	Split_t m_PerUser[1];
};

class CKeyboardKey
{
public:
	char pad[32];
	kbutton_t* m_pKButton;
	CKeyboardKey* m_pNext;
};

class CInput
{
public:
	bool WriteUsercmdDeltaToBuffer(int nSlot, bf_write* pBuffer, int nFrom, int nTo, bool bIsNewCmd); // 5
	CUserCmd* GetUserCmd(int nSlot, int nSequenceNumber); // 8

	void ValidateUserCmd(CUserCmd* pCmd, int nSequenceNumber); // Not in vtable?

	char pad[14];
	bool m_fMouseActive;
	char pad1[44];
	CKeyboardKey* m_pKeys;
	char pad2[108];
	bool m_fCameraInterceptingMouse;
	char pad3[39];
	QAngle m_angPreviousViewAngles;
	char pad4[12];
	float m_flLastForwardMove;
	char pad5[103];
	CUserCmd* m_pCommands;
	CVerifiedUserCmd* m_pVerifiedCommands;
};