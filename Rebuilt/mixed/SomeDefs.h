#pragma once

void __cdecl DevMsg(char const*, ...);
void __cdecl Msg(char const*, ...);
int Warning(const char*, ...);
int DevWarning(int, const char*, ...);
int Error(const char*, ...);

double __cdecl Plat_FloatTime();

float RandomFloat(float, float);
int __cdecl RandomInt(int, int);
int __cdecl RandomFloatExp(float, float, float);

#define MAX_SPLITSCREEN_PLAYERS 2

class CVProfile
{
public:
	void EnterScope(const char*, int, const char*, bool, int);
	void ExitScope();
};

CVProfile* g_VProfCurrentProfile; // Interface?