#pragma once
class Config
{
public:
	inline static SyncMode SyncMode = SyncMode::DeadReckoning;

	inline static uint8 LatencyLevel = 0;
	inline static float BaseLatency[4] = { 0, 30, 80, 200 };
	inline static float Jitter[4] = { 0, 5, 15, 40 };
};

