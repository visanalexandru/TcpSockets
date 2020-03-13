#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include"SocketUtils.h"
#include"Packet.h"
class TcpSocket{

	private:
		int socketId;
	public:
		void connectToAdress(const std::string&adress,unsigned port);
		void sendPacket(const Packet&packet);
		Packet receivePacket();

		friend class TcpListener;

};

#endif
