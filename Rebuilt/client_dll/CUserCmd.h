#pragma once

#include "../mixed/CUserCmd.h"
#include "../mixed/bitbuf.h"
#include "../engine_dll/ConVar.h"

class CUserCmd
{
public:
	~CUserCmd() {}

	CRC32_t GetChecksum();

	void Reset()
	{
		m_nCommandNumber = 0;
		m_nTickCount = 0;
		m_angViewAngles.Reset();
		m_vecAimDirection.Reset();
		m_flForwardMove = 0.f;
		m_flSideMove = 0.f;
		m_flUpMove = 0.f;
		m_nButtons = 0;
		m_nImpulse = 0;
		m_nWeaponSelect = 0;
		m_nWeaponSubType = 0;
		m_nRandomSeed = 0;
		m_nMousedX = 0;
		m_nMousedY = 0;
		m_bHasBeenPredicted = false;
		m_angHeadAngles.Reset();
		m_vecHeadOffset.Reset();
	}

	int m_nCommandNumber;
	int m_nTickCount;
	QAngle m_angViewAngles;
	Vector m_vecAimDirection;
	float m_flForwardMove;
	float m_flSideMove;
	float m_flUpMove;
	int m_nButtons;
	uint8_t m_nImpulse;
	int m_nWeaponSelect;
	int m_nWeaponSubType;
	int m_nRandomSeed;
	__int16 m_nMousedX;
	__int16 m_nMousedY;
	bool m_bHasBeenPredicted;
	QAngle m_angHeadAngles;
	Vector m_vecHeadOffset;
};

struct CVerifiedUserCmd
{
	CUserCmd m_Cmd;
	CRC32_t m_nCrc;
};

ConVar net_showusercmd = ConVar("net_showusercmd", "0", 0, "Show user command encoding");

// [actual address in first opcode] E8 ? ? ? ? F3 0F 10 5F 0C
bool WriteUserCmdDeltaInt(bf_write* pBuffer, const char* szName, int nFrom, int nTo, int nBits)
{
	
}

// [actual address in first opcode] E8 ? ? ? ? F3 0F 10 5F 10
bool WriteUserCmdDeltaFloat(bf_write* pBuffer, const char* szName, float flFrom, float flTo)
{

}

// [actual address in first opcode] E8 ? ? ? ? 0F BF 47 46
bool WriteUserCmdDeltaShort(bf_write* pBuffer, const char* szName, short nFrom, short nTo)
{

}

// [actual address in first opcode] E8 ? ? ? ? 83 C4 04 80 7B 10 00
void WriteUsercmd(bf_write* pBuffer, CUserCmd* pToCmd, CUserCmd* pFromCmd)
{
	if (net_showusercmd.GetInt())
		ConDMsg("WriteUsercmd: from=%d to=%d\n", pFromCmd->m_nCommandNumber, pToCmd->m_nCommandNumber);

	WriteUserCmdDeltaInt(pBuffer, "command_number", pFromCmd->m_nCommandNumber + 1, pToCmd->m_nCommandNumber, 32);
	WriteUserCmdDeltaInt(pBuffer, "tick_count", pFromCmd->m_nTickCount + 1, pToCmd->m_nTickCount, 32);

	WriteUserCmdDeltaFloat(pBuffer, "viewangles[0]", pFromCmd->m_angViewAngles.pitch, pToCmd->m_angViewAngles.pitch);
	WriteUserCmdDeltaFloat(pBuffer, "viewangles[1]", pFromCmd->m_angViewAngles.yaw, pToCmd->m_angViewAngles.yaw);
	WriteUserCmdDeltaFloat(pBuffer, "viewangles[2]", pFromCmd->m_angViewAngles.roll, pToCmd->m_angViewAngles.roll);
	WriteUserCmdDeltaFloat(pBuffer, "aimdirection[0]", pFromCmd->m_vecAimDirection.x, pToCmd->m_vecAimDirection.x);
	WriteUserCmdDeltaFloat(pBuffer, "aimdirection[1]", pFromCmd->m_vecAimDirection.y, pToCmd->m_vecAimDirection.y);
	WriteUserCmdDeltaFloat(pBuffer, "aimdirection[2]", pFromCmd->m_vecAimDirection.z, pToCmd->m_vecAimDirection.z);
	WriteUserCmdDeltaFloat(pBuffer, "forwardmove", pFromCmd->m_flForwardMove, pToCmd->m_flForwardMove);
	WriteUserCmdDeltaFloat(pBuffer, "sidemove", pFromCmd->m_flSideMove, pToCmd->m_flSideMove);
	WriteUserCmdDeltaFloat(pBuffer, "upmove", pFromCmd->m_flUpMove, pToCmd->m_flUpMove);

	WriteUserCmdDeltaInt(pBuffer, "buttons", pFromCmd->m_nButtons, pToCmd->m_nButtons, 32);
	WriteUserCmdDeltaInt(pBuffer, "impulse", pFromCmd->m_nImpulse, pToCmd->m_nImpulse, 8);

	if (WriteUserCmdDeltaInt(pBuffer, "weaponselect", pFromCmd->m_nWeaponSelect, pToCmd->m_nWeaponSelect, 11))
		WriteUserCmdDeltaInt(pBuffer, "weaponsubtype", pFromCmd->m_nWeaponSubType, pToCmd->m_nWeaponSubType, 6);

	WriteUserCmdDeltaShort(pBuffer, "mousedx", pFromCmd->m_nMousedX, pToCmd->m_nMousedX);
	WriteUserCmdDeltaShort(pBuffer, "mousedy", pFromCmd->m_nMousedY, pToCmd->m_nMousedY);
}