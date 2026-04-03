#include "pch.h"
#include "DevScene.h"
#include "ResourceManager.h"
#include "ObjectManager.h"
#include "NetworkManager.h"

void DevScene::OnInit()
{
	{
		Texture* texture = GET_SINGLE(ResourceManager)->LoadTexture(L"WarriorIdle", L"Warrior_Idle.bmp", RGB(255, 255, 255));
		GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_WarriorIdle", texture, { 192, 192 }, 0, 7, 0, 0.5f, true);
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->LoadTexture(L"WarriorRun", L"Warrior_Run.bmp", RGB(255, 255, 255));
		GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_WarriorRun", texture, { 192, 192 }, 0, 5, 0, 0.5f, true);
	}
}

void DevScene::OnUpdate()
{
}

void DevScene::OnRelease()
{
}