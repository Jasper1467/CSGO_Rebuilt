#include "VoiceRecord_DSound.h"

bool VoiceRecord_DSound::RecordStart()
{
    DWORD v3; // [esp+4h] [ebp-8h]
    DWORD v4; // [esp+8h] [ebp-4h]

    if (!m_pCaptureBuffer)
        return false;

    UpdateWrapping();

    if (m_pCaptureBuffer->GetStatus(&v4) < 0 || !(v4 & 1))
        return false;
    
    if (m_pCaptureBuffer->GetCurrentPosition(0, &v3) >= 0)
        m_dwLastReadPos = v3 + m_dwWrapOffset;

    return true;
}

void VoiceRecord_DSound::UpdateWrapping()
{
    if (m_pCaptureBuffer)
    {
        if (!WaitForSingleObject(this->m_hWrapEvent, 0))
            m_dwWrapOffset += m_dwCaptureBufferBytes;
    }
}

int VoiceRecord_DSound::GetRecordedData(__int16* pOut, int nSamples)
{
    DWORD v13;
    if (!m_pCaptureBuffer || m_pCaptureBuffer->GetStatus(&v13) < 0 || !(v13 & 1))
        return 0;

    UpdateWrapping();

    int v6 = 2 * nSamples;
    int a3a = 2 * nSamples;
    
    DWORD dwReadPos;
    if (m_pCaptureBuffer->GetCurrentPosition(0, &dwReadPos) < 0)
        return 0;

    dwReadPos += m_dwWrapOffset;
    DWORD v7 = dwReadPos != v6 ? dwReadPos - v6 : 0;
    if (v7 < m_dwLastReadPos)
        v7 = m_dwLastReadPos;

    void* pData[2];
    DWORD dwDataLen[2];

    if (m_pCaptureBuffer->Lock(
        v7 % m_dwCaptureBufferBytes,
        dwReadPos - v7,
        &pData[0],
        &dwDataLen[0],
        &pData[1],
        &dwDataLen[1],
        0) < 0)
        return 0;

    if (dwDataLen[0] + dwDataLen[1] > a3a)
    {
        m_pCaptureBuffer->Unlock(pData[0], dwDataLen[0], pData[1], dwDataLen[1]);
        return 0;
    }

    memcpy(pOut, pData[0], dwDataLen[0]);
    memcpy(&pOut[dwDataLen[0] / 2], pData[1], dwDataLen[1]);

    m_pCaptureBuffer->Unlock(pData[0], dwDataLen[0], pData[1], dwDataLen[1]);
    m_dwLastReadPos = dwReadPos;

    return (dwDataLen[0] + dwDataLen[1]) >> 1;
}