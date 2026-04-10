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
	obj->SetObjectInfo(info);

	return obj;
}

SyncObject* ObjectManager::SpawnSyncObject(const Protocol::ObjectInfo& info)
{
	// TODO : 타입에 따라 다르게.
	
	Player* obj = Object::CreateObject<Player>();
	obj->SetObjectInfo(info);

	return obj;
}

void ObjectManager::DespawnSyncObject(uint64 id)
{
	Object::DestroyObject(GetSyncObject(id));
}



uint64 ObjectManager::GetMyPlayerId()
{
	return _myPlayer->GetObjectId();
}
