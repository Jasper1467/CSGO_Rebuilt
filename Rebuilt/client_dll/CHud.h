#pragma once

#include "../mixed/CUtlVector.h"
#include "../mixed/Vectors.h"
#include "../mixed/SomeDefs.h"

class CHud;
class CHudElement
{
public:
	
	bool m_bUnknown_4545;
	bool m_bActive;
	bool m_bUnknown;
	int m_nHiddenBits;
	int m_nSplitScreenPlayerSlot;
	bool m_bIgnoreGlobalHudDisable;
	const char* m_szName;
	bool m_bNeedsRemove;
	bool m_bIsParentedToClientDLLRootPanel;
	CUtlVector<int> m_HudRenderGroups;
	CHud* m_pHud;
};

class CBaseHudWeaponSelection : public CHudElement
{
public:

	float m_flSelectionTime;
	static CBaseHudWeaponSelection* s_pInstance[MAX_SPLITSCREEN_PLAYERS];
	bool m_bSelectionVisible;
	void* m_hSelectedWeapon;
};

// NOTE: This is from a while ago
// Don't know how accurate this is but i'll redo this
class CMapOverview
{
public:
	class CMapOverviewIconPackage
	{
	public:

		char pad[132];
		Vector m_vecPosition;
		QAngle m_angAngle;
		Vector m_vecHudPosition;
		float m_flHudRotation;
		float m_flHudScale;
		float m_flRoundStartTime;
		float m_flDeadTime;
		float m_flGhostTime;
		float m_flCurrentAlpha;
		float m_flLastColorUpdate;
		int m_nCurrentVisibilityFlags;
		int m_nIndex;
		int m_nEntityID;
		int m_nHealth;
		wchar_t m_wszName[129];
		int m_nPlayerType;
		int m_nAboveOrBelow;
		float m_flGrenadeExpireTime;
		int m_nIconPackType;
		bool m_bIsActive;
		bool m_bOfflineMap;
		bool m_bIsPlayer;
		bool m_bIsSelected;
		bool m_bIsSpeaking;
		bool m_bIsDead;
		bool m_bIsBot;
		bool m_bIsMobingHostage;
		bool m_bIsSpottedByFriendsOnly;
		bool m_bIsSpotted;
		bool m_bIsRescued;
		bool m_bIsOnLocalTeam;
		bool m_bIsDefuser;
		bool m_bHostageIsUsed;
	};

	char pad[69];
	Vector m_vecMapOrigin;
	float m_flMapSize;
	float m_flMapScale;
	float m_flPixelToRadarScale;
	float m_flWorldToPixelScale;
	float m_flWorldToRadarScale;
	Vector m_RadarViewpointWorld;
	Vector m_RadarViewpointMap;
	float m_RadarRotation;
	Vector m_BombPosition;
	float m_fBombSeenTime;
	float m_fBombAlpha;
};