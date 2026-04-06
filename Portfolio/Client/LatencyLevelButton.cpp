#include "pch.h"
#include "LatencyLevelButton.h"

void LatencyLevelButton::OnInit()
{
	__super::OnInit();
	SetSize({ 150, 50 });
	AddOnClickDelegate(this, &LatencyLevelButton::OnClickButton);
}

void LatencyLevelButton::OnUpdate()
{
	__super::OnUpdate();
}

void LatencyLevelButton::OnRender(HDC hdc)
{
	__super::OnRender(hdc);
	Utils::DrawTextInScreen(hdc, _pos - Pos{ 71, 8 }, L"Change Latency Level");
}

void LatencyLevelButton::OnRelease()
{
	__super::OnRelease();
}

void LatencyLevelButton::OnClickButton()
{
	Config::LatencyLevel++;

	if (Config::LatencyLevel >= 5)
		Config::LatencyLevel = 0;
}
