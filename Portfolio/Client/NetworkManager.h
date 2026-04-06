#pragma once
#include "PacketEnum.h"
#include "PacketUtils.h"
#include "ServerSession.h"

using ServerSessionRef = shared_ptr<class ServerSession>;

struct DelayedPacket
{
    uint64 executeTick;
    ServerSessionRef session;
    vector<BYTE> buffer;
    int32 len;
};

class NetworkManager
{
	DECLARE_SINGLE(NetworkManager)

public:
	void Init();
	void Update();

	ServerSessionRef CreateSession();
    template<typename T>
    void SendPacket(T& pkt)
    {
        if (_session == nullptr)
            return;

        SendBufferRef sendBuffer = PacketUtils::MakeSendBuffer(pkt);

        _session->Send(sendBuffer);
    }

    void EnqueuePacket(ServerSessionRef session, BYTE* buffer, int32 len);

public:
    uint64 GetPing() const { return _ping; }

    void HandleNewPing(uint64 newPing) { _ping = _ping * 0.9f + newPing * 0.1f; }


private:
	ClientServiceRef _service;
	ServerSessionRef _session;

    queue<DelayedPacket> _delayedQueue;

    const float PING_INTERVAL = 1.0f;
    float _pingTimer = PING_INTERVAL;

    uint64 _ping = 0.f;


};

