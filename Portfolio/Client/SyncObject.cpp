#include "pch.h"
#include "SyncObject.h"
#include "ObjectManager.h"

void SyncObject::OnInit()
{
	_objectInfo = new Protocol::ObjectInfo();
}

void SyncObject::OnUpdate()
{

}

void SyncObject::OnRelease()
{
	GET_SINGLE(ObjectManager)->UnregisterSyncObject(this);

	SAFE_DELETE(_objectInfo);
}

void SyncObject::SetInfo(const Protocol::ObjectInfo& info)
{
	_objectInfo->CopyFrom(info);
	_posInfo = _objectInfo->mutable_pos_info();

	SetPos({ _posInfo->pos_x(), _posInfo->pos_y() });

	GET_SINGLE(ObjectManager)->RegisterSyncObject(this);
}