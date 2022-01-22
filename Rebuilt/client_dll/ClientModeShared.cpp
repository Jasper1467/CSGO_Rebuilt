#include "ClientModeShared.h"

#include "C_BasePlayer.h"
#include "../mixed/SomeDefs.h"

float ClientModeShared::GetViewModelFOV()
{
	auto pWeapon = g_pLocalPlayer->GetActiveWeapon();
	if (g_pLocalPlayer && pWeapon)
	{
		auto pController = *(int*)(pWeapon + 13264);
		if (pController &&
			// E8 ? ? ? ? 84 C0 74 5D F3 0F 10 46 1C
			CIronSightController::IsInIronSight(*(float**)(pController)))
		{
			float v4 = *(float*)(pController + 28);
			float v5 = viewmodel_fov.GetFloat();

			return (((54.0f - v5) * v4) + v5);
		}
		else
			return viewmodel_fov.GetFloat();
	}
	else if (viewmodel_offset_randomize.GetBool())
		return RandomFloat(0.f, 1.f) * 14.f + 54.f;
	
	return viewmodel_fov.GetFloat();
}