#include "CTakeDamageInfo.h"

#include "../mixed/StringStuff.h"

static const char* s_szDamageTypeToStrTable[] =
{
	"GENERIC",
	"CRUSH",
	"BULLET",
	"SLASH",
	"BURN",
	"VEHICLE",
	"FALL",
	"BLAST",
	"CLUB",
	"SHOCK",
	"SONIC",
	"ENERGYBEAM",
	"PREVENT_PHYSICS_FORCE",
	"NEVERGIB",
	"ALWAYSGIB",
	"DROWN",
	"PARALYZE",
	"NERVEGAS",
	"POISON",
	"RADIATION",
	"DROWNRECOVER",
	"ACID",
	"SLOWBURN",
	"REMOVENORAGDOLL",
	"PHYSGUN",
	"PLASMA",
	"AIRBOAT",
	"DISSOLVE",
	"BLAST_SURFACE",
	"DIRECT",
	"BUCKSHOT"
};

void CTakeDamageInfo::DebugGetDamageTypeString(unsigned int nDamageType, char* szOutBuf)
{
	int m_nOutBufLen = 512;

	if (!nDamageType)
	{
		int m_nCharsWritten = V_snprintf(szOutBuf, m_nOutBufLen, "%s", "GENERIC");

		nDamageType = 0;

		m_nOutBufLen -= m_nCharsWritten;
		szOutBuf += m_nOutBufLen;
	}

	for (int i = 0; m_nOutBufLen > 0 && i < 30; i++)
	{
		if ((1 << i) & nDamageType)
		{
			int m_nCharsWritten = V_snprintf(szOutBuf, m_nOutBufLen, "%s ", s_szDamageTypeToStrTable[i]);

			m_nOutBufLen -= m_nCharsWritten;
			szOutBuf += m_nOutBufLen;
		}
	}
}