#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include "Socket.h"
#include"Packet.h"
class TcpSocket:public Socket{

	
	public:
		void connectToAdress(const std::string&adress,unsigned port);
		void sendPacket(const Packet&packet);
		Socket::Address getAdress() const;
	


		Packet receivePacket();

		friend class TcpListener;

};

#endif
