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

	_fbIdle = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_WarriorIdle");
	_fbRun = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_WarriorRun");

	_fbRenderer = AddComponent<FlipbookRenderer>();

	_destPosInfo = new Protocol::PosInfo();
}

void Player::OnUpdate()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	_posInfo->set_pos_x(_pos.x);
	_posInfo->set_pos_y(_pos.y);

	if (_isMyPlayer == false)
	{
		switch (Config::SyncMode)
		{
		case SyncMode::Lerp:
		{
			Vec2 dir = Vec2{ _destPosInfo->pos_x(), _destPosInfo->pos_y() } - _pos;

			if (dir.Length() < 1)
			{
				_pos = { _destPosInfo->pos_x(), _destPosInfo->pos_y() };

				_posInfo->set_velocity_x(0);
				_posInfo->set_velocity_y(0);

				SetMoveState(_destPosInfo->state());
			}
			else
			{
				dir.Normalize();
				Vec2 velocity = dir * MOVE_SPEED;

				_pos += velocity * deltaTime;

				_posInfo->set_velocity_x(velocity.x);
				_posInfo->set_velocity_y(velocity.y);
			}
		}
			break;

		case SyncMode::DeadReckoning:
		{
			if (GetMoveState() == Protocol::MOVE_STATE_RUN)
			{
				Vec2 velocity = { _posInfo->velocity_x(), _posInfo->velocity_y() };
				_pos += velocity * deltaTime;
			}
		}
			break;
		}
	}
}

void Player::OnRender(HDC hdc)
{
}

void Player::OnDebugRender(HDC hdc)
{
}

void Player::SetDirection(bool isRight)
{
	if (isRight)
	{
		_fbRenderer->SetFlipX(false);
		_posInfo->set_looking_right(true);
	}
	else
	{
		_fbRenderer->SetFlipX(true);
		_posInfo->set_looking_right(false);
	}
}

void Player::SetObjectInfo(const Protocol::ObjectInfo& info)
{
	__super::SetObjectInfo(info);

	_destPosInfo->CopyFrom(info.pos_info());
}

void Player::SetPosInfo(const Protocol::PosInfo& info)
{
	__super::SetPosInfo(info);

	SetDirection(info.looking_right());
}

void Player::SetMoveState(Protocol::MoveState state)
{
	if (_posInfo->state() == state)
		return;

	_posInfo->set_state(state);

	switch (state)
	{
		case Protocol::MOVE_STATE_IDLE:
			_fbRenderer->SetFlipbook(_fbIdle);
			break;
		case Protocol::MOVE_STATE_RUN:
			_fbRenderer->SetFlipbook(_fbRun);
			break;
	}
}

void Player::SetDestInfo(const Protocol::PosInfo& info)
{
	_destPosInfo->CopyFrom(info);

	SetDirection(info.looking_right());
}

