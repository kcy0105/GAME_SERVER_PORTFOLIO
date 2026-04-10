#include "pch.h"
#include "SyncModeButton.h"

void SyncModeButton::OnInit()
{
	__super::OnInit();
	SetSize({ 150, 50 });
    AddOnClickDelegate(this, &SyncModeButton::OnClickButton);
}

void SyncModeButton::OnUpdate()
{
	__super::OnUpdate();
}

void SyncModeButton::OnRender(HDC hdc)
{
	__super::OnRender(hdc);
	Utils::DrawTextInScreen(hdc, _pos - Pos{ 62, 8 }, L"Change Sync Mode");
}

void SyncModeButton::OnRelease()
{
	__super::OnRelease();
}

void SyncModeButton::OnClickButton()
{
	int mode = static_cast<int>(Config::SyncMode);
	mode = (mode + 1) % static_cast<int>(Protocol::SYNC_MODE_COUNT);
	Config::SyncMode = (Protocol::SyncMode)mode;
}
