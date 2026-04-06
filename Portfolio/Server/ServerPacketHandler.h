#pragma once

#include "Protocol.pb.h"

class ServerPacketHandler
{
public:

    static void Handle_C_LOGIN(SessionRef session, Protocol::C_LOGIN& pkt);

    static void Handle_C_ENTER_GAME(SessionRef session, Protocol::C_ENTER_GAME& pkt);

    static void Handle_C_LEAVE_GAME(SessionRef session, Protocol::C_LEAVE_GAME& pkt);

    static void Handle_C_MOVE(SessionRef session, Protocol::C_MOVE& pkt);

    static void Handle_C_PING(SessionRef session, Protocol::C_PING& pkt);

};
