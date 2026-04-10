#pragma once

#include "Protocol.pb.h"

enum PacketId
{
    C_LOGIN = 10,
    S_LOGIN = 11,
    C_ENTER_GAME = 12,
    S_ENTER_GAME = 13,
    C_LEAVE_GAME = 14,
    S_LEAVE_GAME = 15,
    S_SPAWN = 16,
    S_DESPAWN = 17,
    C_MOVE = 18,
    S_MOVE = 19,
    C_PING = 20,
    S_PONG = 21,
    C_LOG_POS = 22,
    C_SIMULATE_START = 23,
    S_SIMULATE_START = 24,
    C_SIMULATE_FINISH = 25,
    S_SIMULATE_FINISH = 26,
};

template<typename T>
struct PacketIdType
{
};

template<>
struct PacketIdType<Protocol::C_LOGIN>
{
    static const uint16 value = C_LOGIN;
};

template<>
struct PacketIdType<Protocol::S_LOGIN>
{
    static const uint16 value = S_LOGIN;
};

template<>
struct PacketIdType<Protocol::C_ENTER_GAME>
{
    static const uint16 value = C_ENTER_GAME;
};

template<>
struct PacketIdType<Protocol::S_ENTER_GAME>
{
    static const uint16 value = S_ENTER_GAME;
};

template<>
struct PacketIdType<Protocol::C_LEAVE_GAME>
{
    static const uint16 value = C_LEAVE_GAME;
};

template<>
struct PacketIdType<Protocol::S_LEAVE_GAME>
{
    static const uint16 value = S_LEAVE_GAME;
};

template<>
struct PacketIdType<Protocol::S_SPAWN>
{
    static const uint16 value = S_SPAWN;
};

template<>
struct PacketIdType<Protocol::S_DESPAWN>
{
    static const uint16 value = S_DESPAWN;
};

template<>
struct PacketIdType<Protocol::C_MOVE>
{
    static const uint16 value = C_MOVE;
};

template<>
struct PacketIdType<Protocol::S_MOVE>
{
    static const uint16 value = S_MOVE;
};

template<>
struct PacketIdType<Protocol::C_PING>
{
    static const uint16 value = C_PING;
};

template<>
struct PacketIdType<Protocol::S_PONG>
{
    static const uint16 value = S_PONG;
};

template<>
struct PacketIdType<Protocol::C_LOG_POS>
{
    static const uint16 value = C_LOG_POS;
};

template<>
struct PacketIdType<Protocol::C_SIMULATE_START>
{
    static const uint16 value = C_SIMULATE_START;
};

template<>
struct PacketIdType<Protocol::S_SIMULATE_START>
{
    static const uint16 value = S_SIMULATE_START;
};

template<>
struct PacketIdType<Protocol::C_SIMULATE_FINISH>
{
    static const uint16 value = C_SIMULATE_FINISH;
};

template<>
struct PacketIdType<Protocol::S_SIMULATE_FINISH>
{
    static const uint16 value = S_SIMULATE_FINISH;
};

