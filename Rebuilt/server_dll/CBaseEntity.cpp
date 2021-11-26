#include "CBaseEntity.h"
#include "../mixed/SomeDefs.h"
#include "../mixed/EntityStuff.h"

int CheckEntityVelocity(Vector& v)
{
	if (!sv_clamp_unsafe_velocities.GetBool())
		return 1;

	float r = 2000.0f;
	if (
		v.x > -r && v.x < r &&
		v.y > -r && v.y < r &&
		v.z > -r && v.z < r)
		return 1;

	float speed = v.Length();
	if (speed < 2000.0f * 100.0f)
	{
		v *= 2000.0f / speed;
		return 0;
	}

	return -1;
}

static double s_dbLastEntityReasonableEmitTime = -DBL_MAX;
bool CheckEmitReasonablePhysicsSpew()
{
	double dbNow = Plat_FloatTime();
	if (dbNow < s_dbLastEntityReasonableEmitTime || s_dbLastEntityReasonableEmitTime + 5.0 <= dbNow)
		return true;

	return false;
}

void CBaseEntity::SetLocalVelocity(const Vector& vecVelocity)
{
	// E8 ? ? ? ? 5F 5E 5B C3 56

	switch (CheckEntityVelocity(vecVelocity))
	{
	case -1:
		Warning("Discarding SetLocalVelocity(%f,%f,%f) on %s\n", vecVelocity.x, vecVelocity.y, vecVelocity.z, GetDebugName());
		return;
	case 0:
		if (CheckEmitReasonablePhysicsSpew())
			Warning("Clamping SetLocalVelocity(%f,%f,%f) on %s\n", vecVelocity.x, vecVelocity.y, vecVelocity.z, GetDebugName());
		break;
	}

	if (m_vecVelocity != vecVelocity)
	{
		InvalidatePhysicsRecursive(VELOCITY_CHANGED);
		m_vecVelocity = vecVelocity;
	}
}