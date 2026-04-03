#include "pch.h"
#include "GameSession.h"
#include "GameSessionManager.h"
#include "Room.h"
#include "PacketUtils.h"
#include "PacketHandler.h"

void GameSession::OnConnected()
{
	GSessionManager.Add(static_pointer_cast<GameSession>(shared_from_this()));
}

void GameSession::OnDisconnected()
{
	GRoom->LeaveRoom(player.load());

	GSessionManager.Remove(static_pointer_cast<GameSession>(shared_from_this()));

}

void GameSession::OnRecvPacket(BYTE* buffer, int32 len)
{
	PacketHandler::HandlePacket(static_pointer_cast<GameSession>(shared_from_this()), buffer, len);
}

void GameSession::OnSend(int32 len)
{
	//cout << "OnSend Len = " << len << endl;
}