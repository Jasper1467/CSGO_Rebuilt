#pragma once

// NOTE: C_TempEntsSystem::TriggerTempEntity	55 8B EC 83 E4 F8 83 EC 40 A1 ? ? ? ?
// Was very helpful for finding these
enum TERecordingType_e
{
	TE_DYNAMIC_LIGHT = 0x0,
	TE_WORLD_DECAL = 0x1,
	TE_DISPATCH_EFFECT = 0x2,
	TE_MUZZLE_FLASH = 0x3,
	TE_ARMOR_RICOCHET = 0x4,
	TE_METAL_SPARKS = 0x5,
	TE_SMOKE = 0x6,
	TE_SPARKS = 0x7,
	TE_UNKNOWN_10 = 0x8,
	TE_BREAK_MODEL = 0x9,
	TE_GLOW_SPRITE = 0xA,
	TE_PHYSICS_PROP = 0xB,
	TE_SPRITE_SINGLE = 0xC,
	TE_SPIRE_SPRAY = 0xD,
	TE_UNKNOWN_15 = 0xE,
	TE_UNKNOWN_16 = 0xF,
	TE_SHATTER_SURFACE = 0x10,
	TE_DECAL = 0x11,
	TE_PROJECT_DECAL = 0x12,
	TE_EXPLOSION = 0x13,
};

class IRecipientFilter
{
public:
	int GetRecipientCount(); // 3
};

class KeyValues;
class C_TempEntsSystem
{
public:
	bool SuppressTE(IRecipientFilter& Filter) // 1
	{
		if (*(int*)(this + 16) > 0 || *(int*)(this + 8))
			return true;
		else
			return Filter.GetRecipientCount() == 0;
	}

	void TriggerTempEntity(KeyValues* pKeyValues); // 40
};