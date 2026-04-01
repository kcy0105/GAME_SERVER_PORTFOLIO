#pragma once
#include "Player.h"
class MyPlayer : public Player
{
public:
	MyPlayer() {}
	virtual ~MyPlayer() {}

private:
	virtual void OnUpdate() override;
};

