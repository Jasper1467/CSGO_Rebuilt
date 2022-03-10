#pragma once

class bf_read
{
public:
	
};

// client.dll 8B 14 85 ? ? ? ? 23 16
int g_BitWriteMasks[32];

class bf_write
{
public:
	bool CheckForOverflow(int nBits)
	{
		if (m_nCurrentBit + nBits > m_nDataBits)
			m_bOverflow = true;

		return m_bOverflow;
	}

	void WriteOneBitAt(int nBit, int nValue)
	{
		if (!CheckForOverflow(1))
			return;

		// TODO: Continue
	}

	void WriteUBitLong(unsigned int nCurrentData, int nNumBits, bool bCheckRange)
	{
		int v6 = m_nDataBits;
		if (m_nCurrentBit + nNumBits <= v6)
		{
			unsigned int nCurrentBitMask = m_nCurrentBit & 31;
			int nBitsWritten = 32 - nCurrentBitMask;

			m_pData[m_nCurrentBit >> 5] = (nCurrentData << nCurrentBitMask) | m_pData[m_nCurrentBit >> 5] 
				& g_BitWriteMasks[nCurrentBitMask + nNumBits + 32 * nCurrentBitMask];

			if (nBitsWritten < nNumBits)
				m_pData[(m_nCurrentBit >> 5) + 1] = (nCurrentData >> nBitsWritten) | m_pData[(m_nCurrentBit >> 5) + 1]
				& g_BitWriteMasks[nNumBits - nBitsWritten];

			m_nCurrentBit += nNumBits;
		}
		else
		{
			m_nCurrentBit = v6;
			m_bOverflow = true;
		}
	}

	unsigned int* m_pData;
	int m_nDataBytes;
	int m_nDataBits;
	int m_nCurrentBit;
	bool m_bOverflow;
	bool m_bAssertOnOverflow;
	const char* m_szDebugName;
};