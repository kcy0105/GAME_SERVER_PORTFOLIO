#include "pch.h"
#include "ServerPacketHandler.h"
#include "BufferReader.h"
#include "BufferWriter.h"
#include "GameSession.h"
#include "Room.h"
#include "ObjectUtils.h"
#include "chrono"

void ServerPacketHandler::Handle_C_LOGIN(SessionRef session, Protocol::C_LOGIN& pkt)
{
	// TODO: DB에서 Account, 유저 정보 긁어온다
	Protocol::S_LOGIN loginPkt;

	loginPkt.set_success(true);

	static_pointer_cast<GameSession>(session)->SendPacket(loginPkt);
}

void ServerPacketHandler::Handle_C_ENTER_GAME(SessionRef session, Protocol::C_ENTER_GAME& pkt)
{
	PlayerRef player = ObjectUtils::CreatePlayer(static_pointer_cast<GameSession>(session));

	GRoom->HandleEnterPlayer(player);
}

void ServerPacketHandler::Handle_C_LEAVE_GAME(SessionRef session, Protocol::C_LEAVE_GAME& pkt)
{
	PlayerRef player = static_pointer_cast<GameSession>(session)->player.load();
	if (player == nullptr)
		return;

	RoomRef room = player->room.load().lock();
	if (room == nullptr)
		return;

	room->HandleLeavePlayer(player);
}

void ServerPacketHandler::Handle_C_MOVE(SessionRef session, Protocol::C_MOVE& pkt)
{
	PlayerRef player = static_pointer_cast<GameSession>(session)->player.load();
	if (player == nullptr)
		return;

	RoomRef room = player->room.load().lock();
	if (room == nullptr)
		return;

	room->HandleMove(pkt);
}

void ServerPacketHandler::Handle_C_PING(SessionRef session, Protocol::C_PING& pkt)
{
	Protocol::S_PONG pongPkt;
	pongPkt.set_send_tick(pkt.send_tick());

	static_pointer_cast<GameSession>(session)->SendPacket(pongPkt);
}

void ServerPacketHandler::Handle_C_LOG_POS(SessionRef session, Protocol::C_LOG_POS& pkt)
{
	PlayerRef player = static_pointer_cast<GameSession>(session)->player.load();
	if (player == nullptr)
		return;

	RoomRef room = player->room.load().lock();
	if (room == nullptr)
		return;

	room->HandleLogPos(static_pointer_cast<GameSession>(session), pkt);
}

void ServerPacketHandler::Handle_C_HERE(SessionRef session, Protocol::C_HERE& pkt)
{
	string time = std::format("{:%Y-%m-%d %H:%M:%S}", std::chrono::system_clock::now());
	string log = std::format("[{}] ID: {}, Real Pos: ({}, {})", time, pkt.info().object_id(), pkt.info().pos_x(), pkt.info().pos_y());

	cout << log << endl;
}

void ServerPacketHandler::Handle_C_SIMULATE(SessionRef session, Protocol::C_SIMULATE& pkt)
{
	PlayerRef player = static_pointer_cast<GameSession>(session)->player.load();
	if (player == nullptr)
		return;

	RoomRef room = player->room.load().lock();
	if (room == nullptr)
		return;

	room->HandleSimulate(pkt.object_id());

	cout << "========== SIMULATE START ==========" << endl;
}

void ServerPacketHandler::Handle_C_SIMULATE_FINISH(SessionRef session, Protocol::C_SIMULATE_FINISH& pkt)
{
	PlayerRef player = static_pointer_cast<GameSession>(session)->player.load();
	if (player == nullptr)
		return;

	RoomRef room = player->room.load().lock();
	if (room == nullptr)
		return;

	room->HandleSimulateFinish();
}
