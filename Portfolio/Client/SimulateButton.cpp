#include "pch.h"
#include "SimulateButton.h"
#include "ObjectManager.h"
#include "Player.h"
#include "NetworkManager.h"
#include "TimeManager.h"

void SimulateButton::OnInit()
{
	__super::OnInit();
	SetSize({ 150, 50 });
	AddOnClickDelegate(this, &SimulateButton::OnClickButton);
}

void SimulateButton::OnUpdate()
{
	__super::OnUpdate();
}

void SimulateButton::OnRender(HDC hdc)
{
	__super::OnRender(hdc);

	Utils::DrawTextInScreen(hdc, _pos - Pos{ 30, 8 }, L"Simulate");
}

void SimulateButton::OnRelease()
{
	__super::OnRelease();
}

void SimulateButton::OnClickButton()
{
	if (Config::LogPos)
		return;

	GET_SINGLE(TimeManager)->AddJob(0.9f, []() {Config::LogPos = true;});

	Player* notMyPlayer = GET_SINGLE(ObjectManager)->GetNotMyPlayer();
	if (notMyPlayer == nullptr)
		return;
	uint64 notMyPlayerId = notMyPlayer->GetObjectId();

	Protocol::C_SIMULATE pkt;
	pkt.set_object_id(notMyPlayerId);

	GET_SINGLE(NetworkManager)->SendPacket(pkt);
}
