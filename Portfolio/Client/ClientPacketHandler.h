#pragma once

#include "Protocol.pb.h"

class ClientPacketHandler
{
public:

    static void Handle_S_LOGIN(SessionRef session, Protocol::S_LOGIN& pkt);

    static void Handle_S_ENTER_GAME(SessionRef session, Protocol::S_ENTER_GAME& pkt);

    static void Handle_S_LEAVE_GAME(SessionRef session, Protocol::S_LEAVE_GAME& pkt);

    static void Handle_S_SPAWN(SessionRef session, Protocol::S_SPAWN& pkt);

    static void Handle_S_DESPAWN(SessionRef session, Protocol::S_DESPAWN& pkt);

    static void Handle_S_MOVE(SessionRef session, Protocol::S_MOVE& pkt);

    static void Handle_S_PONG(SessionRef session, Protocol::S_PONG& pkt);

    static void Handle_S_SIMULATE_START(SessionRef session, Protocol::S_SIMULATE_START& pkt);

    static void Handle_S_SIMULATE_FINISH(SessionRef session, Protocol::S_SIMULATE_FINISH& pkt);

};
