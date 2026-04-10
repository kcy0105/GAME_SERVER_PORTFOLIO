#include "pch.h"
#include "ClientPacketHandler.h"
#include "BufferReader.h"
#include "DevScene.h"
#include "SceneManager.h"
#include "ServerSession.h"
#include "NetworkManager.h"
#include "ObjectManager.h"
#include "Player.h"
#include "MyPlayer.h"
#include "TimeManager.h"

void ClientPacketHandler::Handle_S_LOGIN(SessionRef session, Protocol::S_LOGIN& pkt)
{
	Protocol::C_ENTER_GAME enterGamePkt;
	GET_SINGLE(NetworkManager)->SendPacket(enterGamePkt);
}

void ClientPacketHandler::Handle_S_ENTER_GAME(SessionRef session, Protocol::S_ENTER_GAME& pkt)
{
	if (pkt.success() == false)
		return;
	
	GET_SINGLE(ObjectManager)->SpawnMyPlayer(pkt.player());
}

void ClientPacketHandler::Handle_S_LEAVE_GAME(SessionRef session, Protocol::S_LEAVE_GAME& pkt)
{
}

void ClientPacketHandler::Handle_S_SPAWN(SessionRef session, Protocol::S_SPAWN& pkt)
{
	for (int i = 0; i < pkt.objects_size(); i++)
	{
		GET_SINGLE(ObjectManager)->SpawnSyncObject(pkt.objects(i));
	}
}

void ClientPacketHandler::Handle_S_DESPAWN(SessionRef session, Protocol::S_DESPAWN& pkt)
{
	for (int i = 0; i < pkt.object_ids_size(); i++)
	{
		GET_SINGLE(ObjectManager)->DespawnSyncObject(pkt.object_ids(i));
	}
}

void ClientPacketHandler::Handle_S_MOVE(SessionRef session, Protocol::S_MOVE& pkt)
{
	auto obj = GET_SINGLE(ObjectManager)->GetSyncObject(pkt.info().object_id());

	auto player = static_cast<Player*>(obj);

	if (player->IsMyPlayer())
	{

	}
	else
	{
		switch (Config::SyncMode)
		{
		case Protocol::SYNC_MODE_SNAP:
			player->SetPosInfo(pkt.info());
			break;
		case Protocol::SYNC_MODE_INTERPOLATION:
			player->SetDestInfo(pkt.info());
			break;
		case Protocol::SYNC_MODE_VELOCITY:
			player->SetPosInfo(pkt.info());
			break;
		case Protocol::SYNC_MODE_DR_SNAP:
		{
			auto info = pkt.mutable_info();

			float deltaTime = (::GetTickCount64() - pkt.timestamp()) / 1000.f;
			Pos pos = { info->pos_x(), info->pos_y() };
			Vec2 velocity = { info->velocity_x(), info->velocity_y() };
			Pos newPos = pos + velocity * deltaTime;

			info->set_pos_x(newPos.x);
			info->set_pos_y(newPos.y);

			player->SetPosInfo(*info);
		}
			break;
		case Protocol::SYNC_MODE_DR_FOLLOW:
		{
			Protocol::PosInfo info;
			info.CopyFrom(pkt.info());

			float deltaTime = (::GetTickCount64() - pkt.timestamp()) / 1000.f;
			Pos pos = { info.pos_x(), info.pos_y() };
			Vec2 velocity = { info.velocity_x(), info.velocity_y() };
			Pos newPos = pos + velocity * deltaTime;

			info.set_pos_x(newPos.x);
			info.set_pos_y(newPos.y);

			player->SetDestInfo(info);
			player->SetMoveState(info.state());
		}
			
			break;
		}
	}
}

void ClientPacketHandler::Handle_S_PONG(SessionRef session, Protocol::S_PONG& pkt)
{
	uint64 ping = ::GetTickCount64() - pkt.send_tick();

	GET_SINGLE(NetworkManager)->HandleNewPing(ping);
}

void ClientPacketHandler::Handle_S_SIMULATE_START(SessionRef session, Protocol::S_SIMULATE_START& pkt)
{
	GET_SINGLE(TimeManager)->PushJob(0.1f, [pkt]()
		{
			int id = pkt.object_id();
			static_cast<Player*>(GET_SINGLE(ObjectManager)->GetSyncObject(pkt.object_id()))->SetLogPos(true);
		});

}

void ClientPacketHandler::Handle_S_SIMULATE_FINISH(SessionRef session, Protocol::S_SIMULATE_FINISH& pkt)
{
	int a = pkt.object_id();
	static_cast<Player*>(GET_SINGLE(ObjectManager)->GetSyncObject(pkt.object_id()))->SetLogPos(false);
}
