#include "pch.h"
#include "Player.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "FlipbookRenderer.h"
#include "ResourceManager.h"
#include "ObjectManager.h"

void Player::OnInit()
{
	__super::OnInit();

	_fb = AddComponent<FlipbookRenderer>();

	_fb->SetFlipbook(GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_WarriorIdle"));
}

void Player::OnUpdate()
{
}

void Player::OnRender(HDC hdc)
{
}

void Player::OnDebugRender(HDC hdc)
{
}
