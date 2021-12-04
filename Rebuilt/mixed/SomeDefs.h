#pragma once

void __cdecl DevMsg(char const*, ...);
void __cdecl Msg(char const*, ...);
int Warning(const char*, ...);
double __cdecl Plat_FloatTime();

#define MAX_SPLITSCREEN_PLAYERS 2