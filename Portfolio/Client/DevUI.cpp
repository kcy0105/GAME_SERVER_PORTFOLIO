#include "pch.h"
#include "DevUI.h"
#include "InputManager.h"
#include "NetworkManager.h"
#include "TimeManager.h"
#include "SyncModeButton.h"
#include "LatencyLevelButton.h"

void DevUI::OnInit()
{
	{
		SyncModeButton* button = UI::CreateUI<SyncModeButton>(this);
		button->SetPos({ 650, 130 });
	}
	{
		LatencyLevelButton* button = UI::CreateUI<LatencyLevelButton>(this);
		button->SetPos({ 650, 200 });
	}
}

void DevUI::OnUpdate()
{
}

void DevUI::OnRender(HDC hdc)
{
	POINT mousePos = GET_SINGLE(InputManager)->GetMousePos();
	uint32 fps = GET_SINGLE(TimeManager)->GetFps();
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	uint64 ping = GET_SINGLE(NetworkManager)->GetPing();

	Utils::DrawTextInScreen(hdc, { 20, 10 }, std::format(L"Mouse({0}, {1})", mousePos.x, mousePos.y));
	Utils::DrawTextInScreen(hdc, { 550, 10 }, std::format(L"FPS({}) DT({})", fps, deltaTime));
	Utils::DrawTextInScreen(hdc, { 550, 30 }, std::format(L"PING({})", ping));

	wstring syncMode;
	switch (Config::SyncMode)
	{
	case SyncMode::Snap:
		syncMode = L"SNAP";
		break;
	case SyncMode::Lerp:
		syncMode = L"LERP";
		break;
	case SyncMode::DeadReckoning:
		syncMode = L"DEAD RECKONING";
		break;
	}
	Utils::DrawTextInScreen(hdc, { 550, 50 }, std::format(L"SYNC MODE({})", syncMode));

	wstring latencyLevel;
	switch (Config::LatencyLevel)
	{
	case 0:
		latencyLevel = L"NO LATENCY";
		break;
	case 1:
		latencyLevel = L"GOOD";
		break;
	case 2:
		latencyLevel = L"NORMAL";
		break;
	case 3:
		latencyLevel = L"BAD";
		break;
	}
	Utils::DrawTextInScreen(hdc, { 550, 70 }, std::format(L"LATENCY LEVEL({})", latencyLevel));
}

void DevUI::OnRelease()
{
}
