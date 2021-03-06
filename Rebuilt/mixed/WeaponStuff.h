#pragma once

enum WeaponModelType_e
{
	WEAPONMODEL_UNRECOGNIZED = 0x0,
	WEAPONMODEL_VIEWMODEL = 0x1,
	WEAPONMODEL_DROPPEDMODEL = 0x2,
	WEAPONMODEL_UNCLASSIFIED = 0x4,
};

enum WeaponMode_e
{
	WEAPONMODE_PRIMARY = 0x0,
	WEAPONMODE_SECONDARY = 0x1,
};

enum WeaponType_e
{
	WEAPONTYPE_KNIFE = 0x0,
	WEAPONTYPE_PISTOL = 0x1,
	WEAPONTYPE_SUBMACHINEGUN = 0x2,
	WEAPONTYPE_RIFLE = 0x3,
	WEAPONTYPE_SHOTGUN = 0x4,
	WEAPONTYPE_MACHINEGUN = 0x5,
	WEAPONTYPE_C4 = 0x6,
	WEAPONTYPE_GRENADE = 0x7,
	WEAPONTYPE_STACKABLEITEM = 0x8,
};

// Ref: server.dll 0F 47 C8 80 7C 24 22 00
#define KNIFE_MAX_DOT_FOR_BACKSTAB 0.475f
// Ref: server.dll B9 30 00 00 00 0F 44 C1
#define KNIFE_RANGE_PRIMARY 48.f
// Ref: server.dll B8 20 00 00 00 B9 30 00 00 00
#define KNIFE_RANGE_SECONDARY 32.f

// Ref: server.dll F3 0F 59 1D ? ? ? ? F3 0F 5C E1
#define GRENADE_SECONDARY_TRANSITION 1.3f
// Ref: 
#define GRENADE_FAILSAFE_MAX_BOUNCES 20
// Ref: server.dll 72 04 6A 11
#define GRENADE_UNDERHAND_THRESHOLD 0.33f