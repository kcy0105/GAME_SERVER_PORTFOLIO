#pragma once
class Config
{
public:
	inline static Protocol::SyncMode SyncMode = Protocol::SYNC_MODE_SNAP;

	inline static uint8 LatencyLevel = 0;
	inline static float BaseLatency[5] = { 0, 20, 50, 80, 110 };
	inline static float Jitter[5] = { 0, 5, 10, 15, 20 };
};

