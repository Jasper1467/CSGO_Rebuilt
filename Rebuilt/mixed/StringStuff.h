#pragma once

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