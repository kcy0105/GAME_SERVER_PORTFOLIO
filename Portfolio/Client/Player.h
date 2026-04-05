#pragma once
#include "SyncObject.h"

class FlipbookRenderer;
class Flipbook;

class Player : public SyncObject
{
public:
	Player() {}
	virtual ~Player() {}

	virtual void OnInit() override;
	virtual void OnUpdate() override;
	virtual void OnRender(HDC hdc) override;
	virtual void OnDebugRender(HDC hdc) override;

public:
	bool IsMyPlayer() const { return _isMyPlayer; }
protected:
	bool _isMyPlayer = false;

private:
	FlipbookRenderer* _fbRenderer = nullptr;
	Flipbook* _fbIdle = nullptr;
	Flipbook* _fbRun = nullptr;

protected:
	const float MOVE_SPEED = 200;

protected:
	void SetDirection(bool isRight);
	

public:
	virtual void SetObjectInfo(const Protocol::ObjectInfo& info) override;
	virtual void SetPosInfo(const Protocol::PosInfo& info) override;
	virtual void SetMoveState(Protocol::MoveState state) override;

	void SetDestInfo(const Protocol::PosInfo& info);

private:
	Protocol::PosInfo* _destPosInfo = nullptr;
};

