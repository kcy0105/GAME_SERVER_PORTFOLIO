#include "pch.h"
#include "ObjectManager.h"
#include "Object.h"
#include "Player.h"
#include "MyPlayer.h"

void ObjectManager::RegisterSyncObject(SyncObject* obj)
{
	uint64 id = obj->GetObjectId();
	_syncObjects[id] = obj;
}

void ObjectManager::UnregisterSyncObject(SyncObject* obj)
{
	uint64 id = obj->GetObjectId();
	_syncObjects[id] = nullptr;
}

MyPlayer* ObjectManager::SpawnMyPlayer(const Protocol::ObjectInfo& info)
{
	MyPlayer* obj = Object::CreateObject<MyPlayer>();
	obj->SetInfo(info);

	return obj;
}

SyncObject* ObjectManager::SpawnSyncObject(const Protocol::ObjectInfo& info)
{
	return nullptr;
}

void ObjectManager::DespawnSyncObject(uint64 id)
{
	Object::DestroyObject(GetSyncObject(id));
}



uint64 ObjectManager::GetMyPlayerId()
{
	return _myPlayer->GetObjectId();
}
