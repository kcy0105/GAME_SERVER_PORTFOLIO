#include "pch.h"
#include "ServerSession.h"
#include "NetworkManager.h"

void ServerSession::OnConnected()
{
	{
		//cout << "Connected To Server" << endl;

		// TEMP
		Protocol::C_LOGIN pkt;

		GET_SINGLE(NetworkManager)->SendPacket(pkt);
	}
}

void ServerSession::OnRecvPacket(BYTE* buffer, int32 len)
{
	GET_SINGLE(NetworkManager)->EnqueuePacket(
		static_pointer_cast<ServerSession>(shared_from_this()),
		buffer,
		len
	);
}

void ServerSession::OnSend(int32 len)
{
}

void ServerSession::OnDisconnected()
{

}
