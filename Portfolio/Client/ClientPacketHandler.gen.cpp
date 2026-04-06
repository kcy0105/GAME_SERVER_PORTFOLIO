#include "pch.h"
#include "ClientPacketHandler.h"
#include "PacketHandlerRegistry.h"
#include "PacketEnum.h"
#include "PacketMacro.h"

REGISTER_PACKET(S_LOGIN, Protocol::S_LOGIN, ClientPacketHandler::Handle_S_LOGIN);
REGISTER_PACKET(S_ENTER_GAME, Protocol::S_ENTER_GAME, ClientPacketHandler::Handle_S_ENTER_GAME);
REGISTER_PACKET(S_LEAVE_GAME, Protocol::S_LEAVE_GAME, ClientPacketHandler::Handle_S_LEAVE_GAME);
REGISTER_PACKET(S_SPAWN, Protocol::S_SPAWN, ClientPacketHandler::Handle_S_SPAWN);
REGISTER_PACKET(S_DESPAWN, Protocol::S_DESPAWN, ClientPacketHandler::Handle_S_DESPAWN);
REGISTER_PACKET(S_MOVE, Protocol::S_MOVE, ClientPacketHandler::Handle_S_MOVE);
REGISTER_PACKET(S_PONG, Protocol::S_PONG, ClientPacketHandler::Handle_S_PONG);
