#include "pch.h"
#include "TimeManager.h"

void TimeManager::Init()
{
	::QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&_frequency));
	::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&_prevCount));
}

void TimeManager::Update()
{
	uint64 currentCount;
	::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&currentCount));

	_deltaTime = (currentCount - _prevCount) / static_cast<float>(_frequency);
	_prevCount = currentCount;

	// 누적 시간
	_accTime += _deltaTime;

	// 타이머 실행
	while (!_jobQueue.empty())
	{
		const Job& job = _jobQueue.top();

		if (job.executeTime > _accTime)
			break;

		job.callback();
		_jobQueue.pop();
	}

	_frameCount++;
	_frameTime += _deltaTime;

	if (_frameTime >= 1.f)
	{
		_fps = static_cast<uint32>(_frameCount / _frameTime);

		_frameTime = 0.f;
		_frameCount = 0;
	}
}

void TimeManager::PushJob(float delay, std::function<void()> func)
{
	Job job;
	job.executeTime = _accTime + delay;
	job.callback = std::move(func);

	_jobQueue.push(job);
}