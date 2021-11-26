#pragma once

class C_BaseEntity
{
public:
	int entindex();
	bool PredictionErrorShouldResetLatchedForAllPredictables() { return true; } // Index 133
};