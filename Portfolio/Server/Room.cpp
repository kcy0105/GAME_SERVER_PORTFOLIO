#include "pch.h"
#include "Room.h"
#include "Player.h"
#include "GameSession.h"

RoomRef GRoom = make_shared<Room>();

Room::Room()
{

}

Room::~Room()
{

}

bool Room::EnterRoom(ObjectRef object, bool randPos)
{
	bool success = AddObject(object);

	if (randPos)
	{
		object->posInfo->set_pos_x(Utils::GetRandom(0.f, 500.f));
		object->posInfo->set_pos_y(Utils::GetRandom(0.f, 500.f));
	}

	// 플레이어가 입장한 거라면
	if (object->IsPlayer())
	{
		auto session = static_pointer_cast<Player>(object)->session.lock();
		if (!session)
		{
			// SOMETHING WRONG
			return false;
		}

		// 입장한 플레이어에게 자신의 정보를 전송한다.
		{
			Protocol::S_ENTER_GAME pkt;
			pkt.set_success(success);

			Protocol::ObjectInfo* info = new Protocol::ObjectInfo();
			info->CopyFrom(*object->objectInfo);
			pkt.set_allocated_player(info);

			session->SendPacket(pkt);
		}

		// 입장한 플레이어에게 이전에 입장한 오브젝트들의 정보를 전송한다.
		{
			Protocol::S_SPAWN pkt;

			for (auto& item : _objects)
			{
				if (item.second->objectInfo->object_id() == object->objectInfo->object_id())
					continue;
				Protocol::ObjectInfo* info = pkt.add_objects();
				info->CopyFrom(*item.second->objectInfo);
			}

			session->SendPacket(pkt);
		}

	}

	// 입장 사실을 다른 플레이어에게 알린다
	{
		Protocol::S_SPAWN pkt;

		Protocol::ObjectInfo* info = pkt.add_objects();
		info->CopyFrom(*object->objectInfo);

		Broadcast(pkt, object->objectInfo->object_id());
	}

	return success;
}

bool Room::LeaveRoom(ObjectRef object)
{
	if (object == nullptr)
		return false;

	const uint64 objectId = object->objectInfo->object_id();
	bool success = RemoveObject(objectId);

	// 퇴장하는 플레이어에게 퇴장 사실을 알린다
	if (object->IsPlayer())
	{
		Protocol::S_LEAVE_GAME pkt;

		if (auto session = static_pointer_cast<Player>(object)->session.lock())
			session->SendPacket(pkt);
	}

	// 다른 플레이어에게 퇴장 사실을 알린다
	{
		Protocol::S_DESPAWN pkt;
		pkt.add_object_ids(objectId);

		if (object->IsPlayer())
			Broadcast(pkt, objectId);
		else
			Broadcast(pkt);
	}

	return success;
}

bool Room::HandleEnterPlayer(PlayerRef player)
{
	return EnterRoom(player, true);
}

bool Room::HandleLeavePlayer(PlayerRef player)
{
	return LeaveRoom(player);
}

void Room::HandleMove(Protocol::C_MOVE pkt)
{
	const uint64 objectId = pkt.info().object_id();
	if (_objects.find(objectId) == _objects.end())
		return;

	if (_objects[objectId]->IsPlayer() == false)
		return;

	PlayerRef player = static_pointer_cast<Player>(_objects[objectId]);
	player->posInfo->CopyFrom(pkt.info());

	{
		Protocol::S_MOVE sendPkt;
		sendPkt.set_timestamp(pkt.timestamp());
		Protocol::PosInfo* info = sendPkt.mutable_info();
		info->CopyFrom(pkt.info());
		Broadcast(sendPkt);
	}
}

void Room::HandleLogPos(Protocol::C_LOG_POS pkt)
{
	string log;
	if (pkt.is_my_player())
	{
		log = std::format("[{}] REAL POS: ({}, {})", pkt.timestamp(), pkt.info().pos_x(), pkt.info().pos_y());
	}	
	else
	{
		string syncMode;
		switch (pkt.sync_mode())
		{
		case Protocol::SYNC_MODE_SNAP:
			syncMode = "SNAP";
			break;
		case Protocol::SYNC_MODE_INTERPOLATION:
			syncMode = "INTERPOLATION";
			break;
		case Protocol::SYNC_MODE_VELOCITY:
			syncMode = "VELOCITY";
			break;
		case Protocol::SYNC_MODE_DR_SNAP:
			syncMode = "DR_SNAP";
			break;
		case Protocol::SYNC_MODE_DR_FOLLOW:
			syncMode = "DR_FOLLOW";
			break;
		}
		log = std::format("[{}] [{}] RENDERED POS: ({}, {})", pkt.timestamp(), syncMode, pkt.info().pos_x(), pkt.info().pos_y());
	}

	cout << log << endl;
}

void Room::HandleSimulate(PlayerRef player)
{
	uint64 playerId = player->objectInfo->object_id();

	Protocol::S_SIMULATE_START pkt;

	pkt.set_object_id(playerId);

	for (auto& item : _objects)
	{
		if (item.first == playerId)
			continue;

		if (!item.second->IsPlayer())
			continue;

		PlayerRef player = static_pointer_cast<Player>(item.second);
		player->session.lock()->SendPacket(pkt);
	}
}

void Room::HandleSimulateFinish(PlayerRef player)
{
	uint64 playerId = player->objectInfo->object_id();

	Protocol::S_SIMULATE_FINISH pkt;
	pkt.set_object_id(playerId);

	for (auto& item : _objects)
	{
		if (item.first == playerId)
			continue;

		if (!item.second->IsPlayer())
			continue;

		PlayerRef player = static_pointer_cast<Player>(item.second);
		player->session.lock()->SendPacket(pkt);
	}
}

RoomRef Room::GetRoomRef()
{
	return static_pointer_cast<Room>(shared_from_this());
}

bool Room::AddObject(ObjectRef object)
{
	// 있다면 문제가 있다.
	if (_objects.find(object->objectInfo->object_id()) != _objects.end())
		return false;

	_objects.insert(make_pair(object->objectInfo->object_id(), object));

	object->room.store(GetRoomRef());

	return true;
}

bool Room::RemoveObject(uint64 objectId)
{
	// 없다면 문제가 있다.
	if (_objects.find(objectId) == _objects.end())
		return false;

	_objects.erase(objectId);

	return true;
}