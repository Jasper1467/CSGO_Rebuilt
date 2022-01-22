#pragma once

#include "../mixed/CUtlVector.h"
#include "../mixed/Vectors.h"
#include "../mixed/SomeDefs.h"
#include "../mixed/Color.h"

class CHud
{
public:
	CHudElement* FindElement(const char* szName);
};

CHud* g_pHud; // Interface

class CHudElement
{
public:
	void SetHud(CHud* pHud)
	{
		m_pHud = pHud;
	}

	bool IsActive()
	{
		return m_bActive;
	}

	void SetActive(bool bActive)
	{
		m_bActive = bActive;
	}

	void SetHiddenBits(int nHiddenBits)
	{
		m_nHiddenBits = nHiddenBits;
	}

	void SetIgnoreGlobalHudDisable(bool bIgnore)
	{
		m_bIgnoreGlobalHudDisable = bIgnore;
	}

	// NOTE: I'm pretty sure i messed something up here
	bool m_bUnknown;
	bool m_bActive;
	bool m_bUnknown1;
	int m_nHiddenBits;
	int m_nSplitScreenPlayerSlot;
	bool m_bIgnoreGlobalHudDisable;
	const char* m_szName;
	bool m_bNeedsRemove;
	bool m_bIsParentedToClientDLLRootPanel;
	CUtlVector<int> m_HudRenderGroups;
	CHud* m_pHud;
};

namespace vgui
{
	typedef unsigned long HFont;
	class Label;
}

#define MIN_HUDHINT_DISPLAY_TIME 7.f

class CHudHintDisplay : public CHudElement
{
public:

	char pad[72];
	bool m_bLastLabelUpdateHack;
	char pad1[275];
	vgui::HFont m_hFont;
	Color m_colBackground;
	vgui::Label* m_pLabel;
	CUtlVector<vgui::Label*> m_Labels;
};

class CBaseHudWeaponSelection : public CHudElement
{
public:

	float m_flSelectionTime;
	static CBaseHudWeaponSelection* s_pInstance[MAX_SPLITSCREEN_PLAYERS];
	bool m_bSelectionVisible;
	void* m_hSelectedWeapon;
};


#define MAPOVERVIEW_MAX_ICONS 28

class CMapOverview
{
public:
	class CMapOverviewIconPackage
	{
	public:

		char pad[186];
		int m_nVisibilityFlags;
		char pad1[8];
		int m_nEntityId;
		int m_nHealth;
		char pad2[132];
		int m_nTeamNum;
	};

	char pad[292];
	float m_flHudScale;
	float m_flUnknown;
	Vector m_vecRadarViewpointWorld;
	Vector m_vecRadarViewpointMap;
	float m_flRadarRotation;
	Vector m_vecBombPosition;
	float m_flBombSeenTime;
	float m_flBombAlpha;
	Vector m_vecDefuserPosition;
	float m_flDefuserSeenTime;
	float m_flDefuserAlpha;
	char pad2[128];
	int m_nLastPlayerIndex;
	char pad3[368];
	CMapOverviewIconPackage m_Players[65];
	wchar_t m_wszLocationText[129];
	char pad4[45982];
	int m_nBombEntIndex;
	int m_nUnknown;
	bool m_bTrackDefusers;
};