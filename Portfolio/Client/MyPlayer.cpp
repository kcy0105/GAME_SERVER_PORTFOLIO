#include "pch.h"
#include "MyPlayer.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "ClientPacketHandler.h"
#include "NetworkManager.h"
#include "DevScene.h"
#include "ObjectManager.h"

void MyPlayer::OnInit()
{
	__super::OnInit();
	GET_SINGLE(ObjectManager)->SetMyPlayer(this);
}

void MyPlayer::OnUpdate()
{
	__super::OnUpdate();

	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	bool forceSendPacket = false;

	if (_simulate)
	{
		_moveInput = { 1, 0 };

		float targetPosX = 200;
		if (_pos.x >= targetPosX)
		{
			_moveInput = { 0, 0 };
			_simulate = false;

			// 종료 패킷 보내기
			Protocol::C_SIMULATE_FINISH pkt;
			GET_SINGLE(NetworkManager)->SendPacket(pkt);
		}
	}
	else
	{
		FillMoveInput();
	}

	// dirty flag
	if (_lastMoveInput != _moveInput)
	{
		forceSendPacket = true;
		_lastMoveInput = _moveInput;
	}

	// state
	if (_moveInput == Vec2{ 0, 0 })
		SetMoveState(Protocol::MOVE_STATE_IDLE);
	else
		SetMoveState(Protocol::MOVE_STATE_RUN);

	// direction
	if (_moveInput.x > 0)
		SetDirection(true);
	else if (_moveInput.x < 0)
		SetDirection(false);

	// move pos & velocity
	if (GetMoveState() == Protocol::MOVE_STATE_RUN)
	{
		Vec2 dir = _moveInput;
		dir.Normalize();

		Vec2 velocity = dir * MOVE_SPEED;
		_pos += velocity * deltaTime;

		_posInfo->set_velocity_x(velocity.x);
		_posInfo->set_velocity_y(velocity.y);
	}
	else
	{
		_posInfo->set_velocity_x(0);
		_posInfo->set_velocity_y(0);
	}

	_movePacketSendTimer -= deltaTime;

	if (_movePacketSendTimer <= 0 || forceSendPacket)
	{
		_movePacketSendTimer = MOVE_PACKET_SEND_INTERVAL;

		Protocol::C_MOVE pkt;
		pkt.set_timestamp(::GetTickCount64());
		pkt.mutable_info()->CopyFrom(*_posInfo);

		GET_SINGLE(NetworkManager)->SendPacket(pkt);
	}
}

void MyPlayer::FillMoveInput()
{
	_moveInput = { 0,0 };

	if (GET_SINGLE(InputManager)->GetButton(KeyType::Up))
		_moveInput += {0, -1};
	if (GET_SINGLE(InputManager)->GetButton(KeyType::Down))
		_moveInput += {0, 1};
	if (GET_SINGLE(InputManager)->GetButton(KeyType::Left))
		_moveInput += {-1, 0};
	if (GET_SINGLE(InputManager)->GetButton(KeyType::Right))
		_moveInput += {1, 0};
}

void MyPlayer::StartSimulate()
{
	SetPos({ 0, 200 });

	GET_SINGLE(TimeManager)->AddJob(1.f, [this]() {_simulate = true;});
}

