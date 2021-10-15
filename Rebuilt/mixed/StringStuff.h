#pragma once

#include <cstdarg>
#include <string.h>

inline const char* V_stristr(char* m_szStr, const char* m_szSearch)
{
    char* v2; // edi
    char* v3; // ebx
    char v4; // al
    char v5; // dh
    unsigned __int8 v6; // dl
    int v7; // ecx
    int v8; // eax
    char v9; // dl
    char* v10; // ecx
    int v11; // ebx
    char v12; // al
    int v13; // esi
    int v14; // eax

    v2 = m_szStr;
    if (!m_szStr)
        return 0;

    v3 = (char*)m_szSearch;

    if (!m_szSearch)
        return 0;

    v4 = *m_szStr;
    if (*m_szStr)
    {
        v5 = *m_szSearch;
        v6 = *m_szSearch - 65;

        while (1)
        {
            if (v4 < 65 || v4 > 90)
                v7 = v4;
            else
                v7 = v4 + 32;

            v8 = v5;

            if (v6 <= 0x19u)
                v8 = v5 + 32;

            if (v7 == v8)
                break;
        LABEL_26:
            v4 = *++v2;
            if (!v4)
                return 0;
        }

        v9 = v3[1];
        v10 = v3 + 1;

        if (!v9)
            return v2;

        v11 = v2 - v3;
        while (1)
        {
            v12 = v10[v11];
            if (!v12)
                break;
            if (v12 < 65 || v12 > 90)
                v13 = v12;
            else
                v13 = v12 + 32;
            v14 = v9;
            if ((unsigned __int8)(v9 - 65) <= 0x19u)
                v14 = v9 + 32;
            if (v13 != v14)
            {
                if (!*v10)
                    return v2;
                v3 = (char*)m_szSearch;
                v6 = *m_szSearch - 65;
                goto LABEL_26;
            }
            v9 = *++v10;
            if (!v9)
                return v2;
        }
    }

    return 0;
}

inline const char* __cdecl V_stristr(const char* m_szStr, const char* m_szSearch)
{
    V_stristr((char*)m_szStr, m_szSearch);
}

int V_vsnprintf(char* m_szDest, int m_nMaxLen, const char* m_szFormat, va_list m_Params)
{
    // Weird stuff happens here that i don't understand yet

    /*
                                                        m_szFormat      = dword ptr  8
V_vsnprintf                                         m_Params        = dword ptr  10h
V_vsnprintf
V_vsnprintf      000 55                                push    ebp
V_vsnprintf+1    004 8B EC                             mov     ebp, esp
V_vsnprintf+3    004 83 E4 F8                          and     esp, 0FFFFFFF8h
V_vsnprintf+6    004 FF 75 10                          push    [ebp+m_Params]  ; int
V_vsnprintf+9    008 6A 00                             push    0               ; struct __crt_locale_pointers *
V_vsnprintf+B    00C FF 75 08                          push    [ebp+m_szFormat] ; int
V_vsnprintf+E    010 52                                push    edx             ; int
V_vsnprintf+F    014 51                                push    ecx             ; int
V_vsnprintf+10   018 E8 DB FF FF FF                    call    sub_10248FF0 <-- Tf is this used for
V_vsnprintf+15   018 8B 08                             mov     ecx, [eax]
V_vsnprintf+17   018 FF 70 04                          push    dword ptr [eax+4] ; int
V_vsnprintf+1A   01C 83 C9 01                          or      ecx, 1
V_vsnprintf+1D   01C 51                                push    ecx             ; int
V_vsnprintf+1E   020 E8 07 0B 53 00                    call    _vsnprintf
V_vsnprintf+23   020 83 C9 FF                          or      ecx, 0FFFFFFFFh
V_vsnprintf+26   020 83 C4 1C                          add     esp, 1Ch
V_vsnprintf+29   004 85 C0                             test    eax, eax
V_vsnprintf+2B   004 0F 48 C1                          cmovs   eax, ecx
V_vsnprintf+2E   004 8B E5                             mov     esp, ebp
V_vsnprintf+30   004 5D                                pop     ebp
V_vsnprintf+31   000 C3                                retn
    */
}

static int V_snprintf(char* m_szDest, int m_nMaxLen, const char* m_szFormat, ...)
{
    int result; // eax
    va_list va; // [esp+20h] [ebp+14h]

    va_start(va, m_szFormat);
    result = V_vsnprintf(m_szDest, m_nMaxLen, m_szFormat, va);

    if (result >= 0 && (m_nMaxLen <= 0 || result < m_nMaxLen))
        return result;

    result = m_nMaxLen - 1;
    m_szDest[m_nMaxLen - 1] = 0;

    return result;
}

const char* V_GetFileName(const char* m_szName)
{
    const char* result; // eax
    char v2; // dl

    if (!m_szName || !*m_szName)
        return m_szName;
    for (result = &m_szName[strlen(m_szName) - 1]; result > m_szName; --result)
    {
        v2 = *(result - 1);
        if (v2 == '\\')
            break;
        if (v2 == '/')
            break;
    }

    return result;
}