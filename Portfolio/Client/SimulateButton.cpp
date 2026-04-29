#include "pch.h"
#include "SimulateButton.h"
#include "ObjectManager.h"
#include "Player.h"
#include "NetworkManager.h"
#include "TimeManager.h"
#include "MyPlayer.h"

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
	GET_SINGLE(ObjectManager)->GetMyPlayer()->SetLogPos(true);

	GET_SINGLE(ObjectManager)->GetMyPlayer()->StartSimulate();

	Protocol::C_SIMULATE_START pkt;

	GET_SINGLE(NetworkManager)->SendPacket(pkt);
}
