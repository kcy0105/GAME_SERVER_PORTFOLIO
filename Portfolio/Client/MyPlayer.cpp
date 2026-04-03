#include "pch.h"
#include "MyPlayer.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "ClientPacketHandler.h"
#include "NetworkManager.h"
#include "DevScene.h"
#include "ObjectManager.h"

void MyPlayer::OnUpdate()
{
	__super::OnUpdate();

	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	bool forceSendPacket = false;

	FillMoveInput();

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

	_movePacketSendTimer -= deltaTime;

	if (_movePacketSendTimer <= 0 || forceSendPacket)
	{
		_movePacketSendTimer = MOVE_PACKET_SEND_DELAY;

		Protocol::C_MOVE pkt;
		pkt.mutable_info()->CopyFrom(*_posInfo);

		GET_SINGLE(NetworkManager)->SendPacket(pkt);
	}

	if (GetMoveState() == Protocol::MOVE_STATE_RUN)
	{
		Vec2 dir = _moveInput;
		dir.Normalize();

		Vec2 velocity = dir * MOVE_SPEED;
		_pos += velocity * deltaTime;

		_posInfo->set_velocity_x(velocity.x);
		_posInfo->set_velocity_y(velocity.y);
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

