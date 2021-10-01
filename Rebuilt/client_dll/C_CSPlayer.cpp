#include "C_CSPlayer.h"

void C_CSPlayer::BuildTransformations(CStudioHdr* m_pHdr, int a3, int a4, int a5, int m_nBoneMask, int m_nBoneComputed)
{
    float* v7; // esi
    int v8; // ebx
    int v9; // eax

    v7 = this;
    C_BaseFlex::BuildTransformations(m_pHdr, a3, a4, a5, m_nBoneMask, m_nBoneComputed);
    v8 = *((_DWORD*)v7 + 2473);
    if (v8)
    {
        if (!*(_DWORD*)(v8 + 10576) && (*(int(__thiscall**)(int))(*(_DWORD*)(v8 + 4) + 32))(v8 + 4))
            sub_101C87E0(v8);
        v9 = *(_DWORD*)(v8 + 10576);
        if (v9 && *(_DWORD*)v9 && (**(_DWORD**)(v9 + 48) & (_DWORD)v7[2476]) != 0 && m_nBoneMask & 0xFFF00)
            sub_10403220(v7, *((_DWORD*)v7 + 2474), m_nBoneMask);
    }
    if (*((_BYTE*)v7 + 39700)
        && *((_DWORD*)v7 + 9816)
        && *((_WORD*)v7 + 313) != 0xFFFF
        && (_BYTE)v7[157] & 1
        && !(*(unsigned __int8(__thiscall**)(float*))(*((_DWORD*)v7 + 2) + 36))(v7 + 2)
        && (!(unsigned __int8)sub_10203920(v7) || (*(unsigned __int8(__thiscall**)(float*))(*(_DWORD*)v7 + 1252))(v7))
        && (*(unsigned __int8(__thiscall**)(float*))(*((_DWORD*)v7 + 1) + 12))(v7 + 1)
        && m_nBoneMask != 512
        && m_nBoneMask >= 1024
        && EnoughBonesAlreadyComputed(m_pHdr, m_nBoneComputed))
    {
        CBoneSnapshot::Update(v7, 0);
        CBoneSnapshot::Update(v7, 0);
    }
}