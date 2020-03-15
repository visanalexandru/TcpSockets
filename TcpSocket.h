#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include "Socket.h"
#include"Packet.h"
class TcpSocket:public Socket{

	
	public:
		Socket::Status connectToAdress(const std::string&adress,unsigned port);
		Socket::Status sendPacket(const Packet&packet);
		Socket::Address getAdress() const;
	
		Socket::Status receivePacket(Packet&packet);

		friend class TcpListener;

};

#endif
