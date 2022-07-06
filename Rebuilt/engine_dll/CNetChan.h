#pragma once

#include "cl_main.h"

#include <cstdint>
#include "../mixed/bitbuf.h"

#define FLOW_OUTGOING 0
#define FLOW_INCOMING 1
#define MAX_FLOWS 2

class INetChannelInfo
{
public:
    enum
    {
        GENERIC = 0x0,
        LOCALPLAYER = 0x1,
        OTHERPLAYERS = 0x2,
        ENTITIES = 0x3,
        SOUNDS = 0x4,
        EVENTS = 0x5,
        TEMPENTS = 0x6,
        USERMESSAGES = 0x7,
        ENTMESSAGES = 0x8,
        VOICE = 0x9,
        STRINGTABLE = 0xA,
        MOVE = 0xB,
        STRINGCMD = 0xC,
        SIGNON = 0xD,
        PAINTMAP = 0xE,
        ENCRYPTED = 0xF,
        TOTAL = 0x10,
    };
};

class INetChannel : public INetChannelInfo
{
public:
   
};

#define CONNECTION_PROBLEM_TIME 4.0f

#define FLOW_INTERVAL 0.25f
#define FLOW_AVG 0.75f

#define NET_FRAMES_BACKUP 128
#define NET_FRAMES_MASK (NET_FRAMES_BACKUP - 1)

#define NET_RATE_MIN 16000.f
#define NET_RATE_MAX 786432.f

enum PacketFlags_e
{
    PACKET_FLAG_RELIABLE = 0x1,
};

struct netpacket_t
{
    char pad[52];
    bf_read m_Message;
    char pad1[35];
    int m_nSize;
    int m_nWireSize;
};

class CNetChan : INetChannel
{
public:

    float GetNetTime(); // 2
    float GetTimeConnected(); // 3
    int GetBufferSize(); // 4
    int GetRate(); // 5
    bool IsTimingOut(); // 7
    float GetTimeSinceLastReceived(); // 22
    void SetTimeout(float flSeconds, bool bForceExact); // 31
    void SetChoked(); // 45

    void GetSequenceData(int& nOutSequenceNr, int& nInSequenceNr, int& nOutSequenceNrAck);

    struct netframe_header_t
    {
        float m_flTime;
        int m_nSize;
        __int16 m_nChoked;
        bool m_bValid;
        float m_flLatency;
    };

    struct netframe_t
    {
        int m_nDropped;
        float m_flAvgLatency;
        float m_flInterpolationAmount;
        unsigned __int16 m_nMsgGroups[INetChannelInfo::TOTAL];
    };

    struct netflow_t
    {
        float m_flNextCompute;
        float m_flAvgBytesPerSecond;
        float m_flAvgPacketsPerSecond;
        float m_flAvgLoss;
        float m_flAvgChoke;
        float m_flAvgLatency;
        float m_flLatency;
        int m_nTotalPackets;
        int m_nTotalBytes;
        int m_nCurrentIndex;
        netframe_header_t m_FrameHeaders[NET_FRAMES_BACKUP];
        netframe_t m_Frames[NET_FRAMES_BACKUP];
        netframe_t* m_pCurrentFrame;
    };

    char pad[20];
    bool m_bProcessingMessages;
    bool m_bShouldDelete;
    bool m_bStopProcessing;
    int m_nOutSequenceNr;
    int m_nInSequenceNr;
    int m_nOutSequenceNrAck;
    int m_nOutReliableState;
    int m_nInReliableState;
    int m_nChokedPackets;
    char pad0[108];
    int m_nSocket;
    char padqzdqzd[4];
    bool m_bWasLastMessageReliable;
    char pad1[100];
    float m_flLastReceived;
    double m_dbConnectTime;
    int m_nRate;
    double m_dbClearTime;
    char pad2[872];
    unsigned int m_nFileRequestCounter;
    char pad3[5];
    bool m_bCompress;
    bool m_bStreamActive;
    netflow_t m_DataFlow[MAX_FLOWS];
    char padqzdzqd[104];
    float m_flTimeOut;
    char pad4[32];
    float m_flRemoteFrameTime;
    float m_flRemoteFrameTimeStdDeviation;
    float m_flRemoteFrameStartTimeStdDeviation;
    int m_nMaxRoutablePayloadSize;
    char pad5[2052];
    int m_nSplitPacketSequence;
    INetChannel* m_pActiveChannel;
};

class INetMessage;

class CNetChanParanoidMode
{
public:
    struct MessageItem_t
    {
        void Dump();

        INetMessage* m_pMsg;
        size_t m_nMessageSize;
        int m_nType;
        int m_nGroup;
        int m_nStartBit;
        int m_nEndBit;
        unsigned char m_Message[128];
        char m_szName[32];
        char m_szDesc[128];
    };

};