#pragma once
#include "Object.h"

class SyncObject : public Object
{
public:
	SyncObject() {}
	virtual ~SyncObject() {}

	virtual void OnInit() override;
	virtual void OnUpdate() override;
	virtual void OnRelease() override;

	virtual void SetPos(Pos pos) override;

	virtual void SetObjectInfo(const Protocol::ObjectInfo& info);
	virtual void SetPosInfo(const Protocol::PosInfo& info);
	virtual void SetMoveState(Protocol::MoveState state);

	Protocol::PosInfo GetPosInfo() { return *_posInfo; }
	uint64 GetObjectId()	const { return _objectInfo->object_id(); }
	Protocol::MoveState GetMoveState() const { return _posInfo->state(); }

	bool IsPlayer() { return _isPlayer; }


protected:
	Protocol::ObjectInfo* _objectInfo = nullptr;
	Protocol::PosInfo* _posInfo = nullptr;

	bool _isPlayer = false;
};

