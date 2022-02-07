#pragma once

#include "CUserCmd.h"
#include "../mixed/bitbuf.h"

#define MULTIPLAYER_BACKUP 150

class CInput
{
public:
	bool WriteUsercmdDeltaToBuffer(int nSlot, bf_write* pBuffer, int nFrom, int nTo, bool bIsNewCmd); // 5
	CUserCmd* GetUserCmd(int nSlot, int nSequenceNumber); // 8

	void ValidateUserCmd(CUserCmd* pCmd, int nSequenceNumber); // Not in vtable?
};