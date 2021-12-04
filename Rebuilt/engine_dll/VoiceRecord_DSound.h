#pragma once
#include <Windows.h>
#include <dsound.h>

class VoiceRecord_DSound
{
public:
	void Release()
	{
		delete this;
	}

	bool RecordStart();
	void* nullsub_1();
	void UpdateWrapping();
	int GetRecordedData(__int16* pOut, int nSamples);
	bool Init(int nSampleRate);

	HMODULE m_hDSoundDll;
	LPDIRECTSOUNDCAPTURE m_pCapture;
	LPDIRECTSOUNDCAPTUREBUFFER m_pCaptureBuffer;
	DWORD m_dwCaptureBufferBytes;
	DWORD m_dwWrapOffset;
	HANDLE m_hWrapEvent;
	DWORD m_dwLastReadPos;
};