#pragma once

#include "CBasePlayerAnimState.h"
#include "../mixed/AnimationStuff.h"

class CCSPlayer;

class CCSPlayerAnimState : public CBasePlayerAnimState
{
public:
	bool HandleJumping();

	char pad[44];
	bool m_bJumping;
	float m_flJumpStartTime;
	bool m_bJumpThisFrame;
	float m_flPostLandCrouchEndTime;
	bool m_bReloading;
	float m_flReloadCycle;
	int m_nReloadSequence;
	float m_flReloadEndTime;
	bool m_bSilencerChange;
	char pad1[12];
	float m_flFlashedAmount;
	float m_flLastFlashDuration;
	char pad2[4];
	float m_flFLinchStartTime;
	float m_flFlinchLength;
	int m_nFlinchSequence;
	float m_flTauntStartTime;
	float m_flTauntLength;
	int m_nTauntSequence;
	bool m_bIsDeploying;
	int m_nDeployingSequence;
	float m_flDeployCycle;
	int m_nCurrentAimSequence;
	float m_flTargetMaxSpeed;
	float m_flCurrentMaxSpeed;
	int m_nIdleFireSequence;
	bool m_bFiring;
	int m_nFireSequence;
	float m_flFireCycle;
	PlayerAnimEvent_e m_nDelayedFireEvent;
	PlayerAnimEvent_e m_nActiveFireEvent;
	char pad3[16];
	bool m_bTryingToRunAfterJump;
	int m_nCurrentActivity;
	CCSPlayer* m_pPlayer;
	int m_nDeployedWeaponId;
	float m_flWeaponSwitchTime;
	void* m_pHelpers;
};