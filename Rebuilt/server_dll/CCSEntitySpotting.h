#pragma once

#define ENTITY_SPOT_FREQUENCY 0.5f

class CCSEntitySpotting/* : public CAutoGameSystemPerFrame*/
{
public:
	enum SpotRules_e
	{
		SPOT_RULE_ENEMY = 0x1,
		SPOT_RULE_CT = 0x2,
		SPOT_RULE_T = 0x4,
		SPOT_RULE_ALWAYS_SEEN_BY_FRIEND = 0x8,
		SPOT_RULE_ALWAYS_SEEN_BY_CT = 0x10,
		SPOT_RULE_ALWAYS_SEEN_BY_T = 0x20,
	};

	const char* Name()
	{
		return "CCSEntitySpotting";
	}
	
	char pad[8]; // These are from CAutoGameSystemPerFrame

	float m_flLastUpdate;
};