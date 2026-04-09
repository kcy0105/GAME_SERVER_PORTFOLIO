#include "pch.h"
#include "SyncObject.h"
#include "ObjectManager.h"

void SyncObject::OnInit()
{
	_objectInfo = new Protocol::ObjectInfo();
	_posInfo = _objectInfo->mutable_pos_info();
}

void SyncObject::OnUpdate()
{

}

void SyncObject::OnRelease()
{
	GET_SINGLE(ObjectManager)->UnregisterSyncObject(this);

	SAFE_DELETE(_objectInfo);
}

void SyncObject::SetPos(Pos pos)
{
	__super::SetPos(pos);

	_posInfo->set_pos_x(pos.x);
	_posInfo->set_pos_y(pos.y);
}

void SyncObject::SetObjectInfo(const Protocol::ObjectInfo& info)
{
	SetPos({ info.pos_info().pos_x(), info.pos_info().pos_y() });
	SetMoveState(info.pos_info().state());

	_objectInfo->CopyFrom(info);
	_posInfo = _objectInfo->mutable_pos_info();

	GET_SINGLE(ObjectManager)->RegisterSyncObject(this);
}

void SyncObject::SetPosInfo(const Protocol::PosInfo& info)
{
	SetPos({ info.pos_x(), info.pos_y() });
	SetMoveState(info.state());

	_posInfo->CopyFrom(info);
}

void SyncObject::SetMoveState(Protocol::MoveState state)
{
	if (_posInfo->state() == state)
		return;

	_posInfo->set_state(state);
}

