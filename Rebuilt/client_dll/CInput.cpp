#include "CInput.h"
#include "../mixed/SomeDefs.h"

bool CInput::WriteUsercmdDeltaToBuffer(int nSlot, bf_write* pBuffer, int nFrom, int nTo, bool bIsNewCmd)
{
	CUserCmd v13;
	v13.Reset();

	int nStartBit = *((uintptr_t*)pBuffer + 3);

	CUserCmd* pFromCmd;
	if (nFrom == -1)
		pFromCmd = &v13;
	else
	{
		pFromCmd = GetUserCmd(nSlot, nFrom);
		if (pFromCmd)
			ValidateUserCmd(pFromCmd, nFrom);
		else
			pFromCmd = &v13;
	}

	CUserCmd* pToCmd = GetUserCmd(nSlot, nTo);
	if (pToCmd)
		ValidateUserCmd(pToCmd, nTo);
	else
		pToCmd = &v13;

	WriteUsercmd(pBuffer, pToCmd, pFromCmd);

	if (*((uintptr_t*)pBuffer + 16)) // m_bIsOverflowed
	{
		int nCurrentBit = *((uintptr_t*)pBuffer + 3);
		Msg("WARNING! User command buffer overflow(%i %i), last cmd was %i bits long\n", nFrom, nTo, nCurrentBit - nStartBit);

		return false;
	}

	return true;
}

void CInput::ValidateUserCmd(CUserCmd* pCmd, int nSequenceNumber)
{
	CVerifiedUserCmd* pVerifiedCommands = (CVerifiedUserCmd*)(uintptr_t(this) + 0xF8);
	CVerifiedUserCmd* pVerified = &pVerifiedCommands[nSequenceNumber% MULTIPLAYER_BACKUP];

	if (pCmd->GetChecksum() != pVerified->m_nCrc)
		pCmd = &pVerified->m_Cmd;
}