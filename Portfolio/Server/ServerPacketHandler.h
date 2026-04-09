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

    static void Handle_C_LOG_POS(SessionRef session, Protocol::C_LOG_POS& pkt);

    static void Handle_C_HERE(SessionRef session, Protocol::C_HERE& pkt);

    static void Handle_C_SIMULATE(SessionRef session, Protocol::C_SIMULATE& pkt);

    static void Handle_C_SIMULATE_FINISH(SessionRef session, Protocol::C_SIMULATE_FINISH& pkt);

};
