#include "pch.h"
#include "Object.h"
#include "Player.h"

atomic<uint64> Object::s_idGenerator = 1;

Object::Object()
{
	objectInfo = new Protocol::ObjectInfo();
	posInfo = new Protocol::PosInfo();
	objectInfo->set_allocated_pos_info(posInfo);

	const uint64 newId = s_idGenerator.fetch_add(1);
	objectInfo->set_object_id(newId);
	posInfo->set_object_id(newId);
}

Object::~Object()
{
	delete objectInfo;
}
