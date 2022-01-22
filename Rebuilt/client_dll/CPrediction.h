#pragma once

#include "../engine_dll/ConVar.h"
#include "../mixed/CGlobalVarsBase.h"
#include <cstdint>
#include <cstddef>
#include "../mixed/SomeDefs.h"

ConVar cl_predict = ConVar("cl_predict", "1.5", 0x400200, "Perform client side prediction.");

ConVar cl_pred_optimize = ConVar("cl_pred_optimize", "2", 0,
	"Optimize for not copying data if didn't receive a network update (1), and also for not repredicting if there were no errors (2).");

#define MAX_PREDICTION_ERROR 64.f
#define MIN_PREDICTION_EPSILON 0.5f

class CHudElement;
class CPrediction
{
public:
	void Init();
	void Update(int nStartFrame, bool bValidFrame, int nIncomingAck, int nOutgoingCmd);

	void _Update(int nSlot, bool bReceivedNewWorldUpdate, bool bValidFrame, int nIncomingAck, int nOutCmd);

	struct Split_t
	{
		bool m_bIsFirstTimePredicted;
		std::byte pad0[3];
		int m_nCommandsPredicted;
		int m_nServerCommandsAcknowledged;
		int m_nPreviousAckHadErrors;
		float m_flIdealPitch;
		int m_nLastCommandAcknowledged;
		bool m_bPreviousAckErrorTriggersFullLatchReset;
		void* m_EntitiesWithPredictionErrorsInLastAck;
		bool m_bPerformedTickShift;
	};

	uintptr_t m_hLastGround;
	bool m_bInPrediction;
	bool m_bIsFirstTimePredicted;
	bool m_bEnginePaused;
	bool m_bOldCLPredictValue;
	int m_nPreviousStartFrame;
	int m_nIncomingPacketNumber;
	float m_flLastServerWorldTimeStamp;
	Split_t m_Split[MAX_SPLITSCREEN_PLAYERS];
	CGlobalVarsBase m_SavedVars;
	char pad[76];
	bool m_bPlayerOriginTypedescriptionSearched;
	char pad1[22];
	void* m_pPDumpPanel;
};