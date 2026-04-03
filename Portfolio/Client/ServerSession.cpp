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

void ServerSession::OnDisconnected()
{

}
