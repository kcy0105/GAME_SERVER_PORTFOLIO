#include "pch.h"
#include "ServerPacketHandler.h"
#include "PacketHandlerRegistry.h"
#include "PacketEnum.h"
#include "PacketMacro.h"

REGISTER_PACKET(C_LOGIN, Protocol::C_LOGIN, ServerPacketHandler::Handle_C_LOGIN);
REGISTER_PACKET(C_ENTER_GAME, Protocol::C_ENTER_GAME, ServerPacketHandler::Handle_C_ENTER_GAME);
REGISTER_PACKET(C_LEAVE_GAME, Protocol::C_LEAVE_GAME, ServerPacketHandler::Handle_C_LEAVE_GAME);
REGISTER_PACKET(C_MOVE, Protocol::C_MOVE, ServerPacketHandler::Handle_C_MOVE);
REGISTER_PACKET(C_PING, Protocol::C_PING, ServerPacketHandler::Handle_C_PING);
REGISTER_PACKET(C_LOG_POS, Protocol::C_LOG_POS, ServerPacketHandler::Handle_C_LOG_POS);
REGISTER_PACKET(C_HERE, Protocol::C_HERE, ServerPacketHandler::Handle_C_HERE);
REGISTER_PACKET(C_SIMULATE, Protocol::C_SIMULATE, ServerPacketHandler::Handle_C_SIMULATE);
REGISTER_PACKET(C_SIMULATE_FINISH, Protocol::C_SIMULATE_FINISH, ServerPacketHandler::Handle_C_SIMULATE_FINISH);
