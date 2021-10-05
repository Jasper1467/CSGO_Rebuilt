#pragma once

#include "cl_main.h"

#include <cstdint>

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
    char pad_0000[20];           //0x0000
    bool m_bProcessingMessages;  //0x0014
    bool m_bShouldDelete;        //0x0015
    char pad_0016[2];            //0x0016
    int32_t m_nOutSequenceNr;    //0x0018 last send outgoing sequence number
    int32_t m_nInSequenceNr;     //0x001C last received incoming sequnec number
    int32_t m_nOutSequenceNrAck; //0x0020 last received acknowledge outgoing sequnce number
    int32_t m_nOutReliableState; //0x0024 state of outgoing reliable data (0/1) flip flop used for loss detection
    int32_t m_nInReliableState;  //0x0028 state of incoming reliable data
    int32_t m_nChokedPackets;    //0x002C number of choked packets
    char pad_0030[1044];         //0x0030
};

#define CONNECTION_PROBLEM_TIME 4.0f

#define FLOW_INTERVAL 0.25f
#define FLOW_AVG 0.75f

#define NET_FRAMES_BACKUP 128

class CNetChan : INetChannel
{
public:
    bool IsTimingOut();
    void SetChoked();
    void SetTimeout(float m_flSeconds, bool m_bForceExact);

    struct netframe_header_t
    {
        __int16 m_nChoked;
        bool m_bValid;
        float m_flLatency;
    };


    float m_flLastReceived; // this[67]
	float m_flTimeout; // this[4183]
};