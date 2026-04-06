#include "pch.h"
#include "NetworkManager.h"
#include "Service.h"
#include "ThreadManager.h"
#include "ServerSession.h"
#include "TimeManager.h"

void NetworkManager::Init()
{
	SocketUtils::Init();

	_service = make_shared<ClientService>(
		NetAddress(L"127.0.0.1", 7777),
		make_shared<IocpCore>(),
		[=]() { return CreateSession(); }, // TODO : SessionManager µî
		1);

	assert(_service->Start());

	/*for (int32 i = 0; i < 5; i++)
	{
		GThreadManager->Launch([=]()
			{
				while (true)
				{
					service->GetIocpCore()->Dispatch();
				}
			});
	}*/
}

void NetworkManager::Update()
{
	_service->GetIocpCore()->Dispatch(0);
	
	while (!_delayedQueue.empty())
	{
		uint64 nowTick = ::GetTickCount64();

		DelayedPacket pkt = _delayedQueue.front();

		if (nowTick >= pkt.executeTick)
		{
			PacketHandler::HandlePacket(pkt.session, pkt.buffer.data(), pkt.len);
			_delayedQueue.pop();
		}
		else
		{
			break;
		}
	}

	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	_pingTimer -= deltaTime;

	if (_pingTimer <= 0)
	{
		_pingTimer = PING_INTERVAL;

		Protocol::C_PING pkt;
		pkt.set_send_tick(::GetTickCount64());

		SendPacket(pkt);
	}

}

ServerSessionRef NetworkManager::CreateSession()
{
	return _session = make_shared<ServerSession>();
}

void NetworkManager::EnqueuePacket(ServerSessionRef session, BYTE* buffer, int32 len)
{
	DelayedPacket pkt;
	pkt.session = session;
	pkt.len = len;

	pkt.buffer.resize(len);
	memcpy(pkt.buffer.data(), buffer, len);

	float nowTick = ::GetTickCount64();
	float latency = Config::BaseLatency[Config::LatencyLevel] + ((rand() % 1000) / 1000.f) * 2 * Config::Jitter[Config::LatencyLevel] - Config::Jitter[Config::LatencyLevel];
	pkt.executeTick = nowTick + latency;

	_delayedQueue.push(pkt);
}
