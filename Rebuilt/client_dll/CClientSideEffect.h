#pragma once
#include "../mixed/SomeDefs.h"

class CClientSideEffect
{
public:
	~CClientSideEffect()
	{

	}

	void Draw(double dbFrameTime); // __purecall :(

	const char* GetName()
	{
		return m_szName;
	}

	bool IsActive()
	{
		return m_bActive;
	}

	void Destroy()
	{
		m_bActive = false;
	}

	const char* m_szName;
	bool m_bActive;
};

// Ref: 3D 00 01 00 00 7C 1C
#define MAX_EFFECTS 256

class CEffectsList
{
public:
	void AddEffect(CClientSideEffect* pEffect)
	{
		if (pEffect)
		{
			if (m_nEffects < MAX_EFFECTS)
			{
				m_pEffects[m_nEffects] = pEffect;
				++m_nEffects;
			}
			else
				DevWarning(1, "No room for effect %s\n", pEffect->GetName());
		}
	}

	void DrawEffects(double dbFrameTime)
	{
		if (*(int*)(g_VProfCurrentProfile + 4108))
			g_VProfCurrentProfile->EnterScope("CEffectsList::DrawEffects", 0, "Particle/Effect_Rendering", 0, 4);

		for (int i = m_nEffects - 1; i >= 0; i--)
		{
			CClientSideEffect* pEffect = m_pEffects[i];

			pEffect->Draw(dbFrameTime);

			if (!pEffect->IsActive())
			{
				if (i < m_nEffects || i < 0)
					continue;

				m_nEffects--;

				if (m_nEffects > 0 || m_nEffects != i)
					m_pEffects[i] = m_pEffects[m_nEffects];

				pEffect->Destroy();
				delete pEffect;
			}
		}

		if (g_VProfCurrentProfile)
			g_VProfCurrentProfile->ExitScope();
	}

	void Flush()
	{
		for (int i = m_nEffects - 1; i >= 0; i--)
		{
			CClientSideEffect* pEffect = m_pEffects[i];
			if (pEffect)
			{
				m_nEffects--;

				if (m_nEffects > 0 || m_nEffects != i)
					m_pEffects[i] = m_pEffects[m_nEffects];

				pEffect->Destroy();
				delete pEffect;
			}
		}
	}

	int m_nEffects;
	CClientSideEffect* m_pEffects[256];
};