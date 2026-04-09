#pragma once

class MapObject;
class SyncObject;
class Player;
class WaterBomb;
class MyPlayer;

class ObjectManager
{
	DECLARE_SINGLE(ObjectManager)

	/*==============
	   SyncObjects
	================*/
public:
	void RegisterSyncObject(SyncObject* obj);
	void UnregisterSyncObject(SyncObject* obj);
	SyncObject* GetSyncObject(uint64 id) { return _syncObjects[id]; }

private:
	unordered_map<uint64, SyncObject*> _syncObjects;


	/*==================
	   Spawn & Despawn
	===================*/
public:
	MyPlayer* SpawnMyPlayer(const Protocol::ObjectInfo& info);
	SyncObject* SpawnSyncObject(const Protocol::ObjectInfo& info);
	void DespawnSyncObject(uint64 id);


	/*===========
	    Player
	============*/
public:
	void SetMyPlayer(MyPlayer* myPlayer) { _myPlayer = myPlayer; }
	MyPlayer* GetMyPlayer() { return _myPlayer; }
	uint64 GetMyPlayerId();

	Player* GetNotMyPlayer();

private:
	MyPlayer* _myPlayer = nullptr;


};

