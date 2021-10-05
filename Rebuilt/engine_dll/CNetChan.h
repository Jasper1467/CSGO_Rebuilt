#pragma once

#define FLOW_OUTGOING 0
#define FLOW_INCOMING 1
#define MAX_FLOWS 2

class INetChannelInfo
{
public:

};

class INetChannel : INetChannelInfo
{
public:

};

class CNetChan : INetChannel
{
public:
	bool IsTimingOut();
	void SetChoked();

	char pad_0000[20];
	bool m_bProcessingMessages;
	bool m_bShouldDelete;
	char pad_0016[2];
	int m_nOutSequenceNr;
	int m_nInSequenceNr;
	int m_nOutSequenceNrAck;
	int m_nOutReliableState;
	int m_nInReliableState;
	int m_nChokedPackets;
	char pad_0030[1044];
};