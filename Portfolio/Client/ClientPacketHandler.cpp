#include "pch.h"
#include "ClientPacketHandler.h"
#include "BufferReader.h"
#include "DevScene.h"
#include "SceneManager.h"
#include "ServerSession.h"
#include "NetworkManager.h"
#include "ObjectManager.h"

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
	// TODO
}
