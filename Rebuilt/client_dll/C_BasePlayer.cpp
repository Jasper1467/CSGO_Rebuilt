#include "C_BasePlayer.h"

#include "../mixed/EntityStuff.h"

bool C_BasePlayer::IsAlive()
{
	return m_lifeState == LIFE_ALIVE;
}