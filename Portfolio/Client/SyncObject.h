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

	void SetInfo(const Protocol::ObjectInfo& info);
	uint64 GetObjectId()	const { return _objectInfo->object_id(); }

protected:
	Protocol::ObjectInfo* _objectInfo = nullptr;
	Protocol::PosInfo* _posInfo = nullptr;
};

