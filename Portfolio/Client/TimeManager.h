#pragma once
#include <functional>
#include <vector>

class TimeManager
{
	DECLARE_SINGLE(TimeManager)

public:
	void Init();
	void Update();

	uint32 GetFps() { return _fps; }
	float GetDeltaTime() { return _deltaTime; }

	// 추가
	void PushJob(float delay, std::function<void()> func);

private:
	uint64 _frequency = 0;
	uint64 _prevCount = 0;
	float _deltaTime = 0.f;

private:
	uint32 _frameCount = 0;
	float _frameTime = 0.f;
	uint32 _fps = 0;

private:
	// 타이머 구조체
	struct Job
	{
		float executeTime;
		std::function<void()> callback;

		bool operator<(const Job& other) const
		{
			return executeTime > other.executeTime; // min-heap
		}
	};

	float _accTime = 0.f;
	std::priority_queue<Job> _jobQueue;
};