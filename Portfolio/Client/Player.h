#pragma once
#include "SyncObject.h"

class FlipbookRenderer;

class Player : public SyncObject
{
public:
	Player() {}
	virtual ~Player() {}

	virtual void OnInit() override;
	virtual void OnUpdate() override;
	virtual void OnRender(HDC hdc) override;
	virtual void OnDebugRender(HDC hdc) override;

protected:
	FlipbookRenderer* _fb = nullptr;
};

