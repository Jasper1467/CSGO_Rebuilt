#pragma once

#include "../engine_dll/ConVar.h"

ConVar cl_predict = ConVar("cl_predict", "1.5", 0x400200, "Perform client side prediction.");

ConVar cl_pred_optimize = ConVar("cl_pred_optimize", "2", 0,
	"Optimize for not copying data if didn't receive a network update (1), and also for not repredicting if there were no errors (2).");

class CPrediction
{
public:

};