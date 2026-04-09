#pragma once

#include "Player.h"
#include "GameSession.h"

class Room : public enable_shared_from_this<Room>
{
public:
	Room();
	virtual ~Room();

public:
	bool EnterRoom(ObjectRef object, bool randPos = true);
	bool LeaveRoom(ObjectRef object);

	bool HandleEnterPlayer(PlayerRef player);
	bool HandleLeavePlayer(PlayerRef player);
	void HandleMove(Protocol::C_MOVE pkt);
	void HandleLogPos(GameSessionRef session, Protocol::C_LOG_POS pkt);
	void HandleSimulate(uint64 objectId);
	void HandleSimulateFinish();

public:
	RoomRef GetRoomRef();

private:
	bool AddObject(ObjectRef object);
	bool RemoveObject(uint64 objectId);

public:
	template<typename T>
	void Broadcast(T& pkt, uint64 exceptId = 0)
	{
		for (auto& item : _objects)
		{
			if (item.second->IsPlayer() == false)
				continue;
			if (item.second->objectInfo->object_id() == exceptId)
				continue;

			PlayerRef player = static_pointer_cast<Player>(item.second);

			if (auto session = player->session.lock())
			{
				session->SendPacket(pkt);
			}
		}
	}

private:
	unordered_map<uint64, ObjectRef> _objects;

	weak_ptr<GameSession> _logPosSession;
};



extern RoomRef GRoom;