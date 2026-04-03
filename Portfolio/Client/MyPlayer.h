#pragma once
#include "Player.h"
class MyPlayer : public Player
{
public:
	MyPlayer() { _isMyPlayer = true; }
	virtual ~MyPlayer() {}

private:
	virtual void OnUpdate() override;

protected:
	const float MOVE_PACKET_SEND_DELAY = 0.2f;
	float _movePacketSendTimer = MOVE_PACKET_SEND_DELAY;

	Vec2 _moveInput;
	Vec2 _lastMoveInput;
	
	

private:
	void FillMoveInput();

	

};

