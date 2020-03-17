#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include "Socket.h"
#include"Packet.h"
class TcpSocket:public Socket{
	private:
		Socket::Status receiveAll(char*data,int size);//receives chunks until total received=size
		Socket::Status sendAll(const char*data,int size);//sends chunks until total sent=size

	public:
		Socket::Status connectToAdress(const std::string&adress,unsigned port);
		Socket::Status sendPacket(const Packet&packet);
		Socket::Address getAdress() const;

		Socket::Status sendData(const void*data,int size,int&sent);
		Socket::Status receiveData(void*receive,int size,int&received);

		Socket::Status receivePacket(Packet&packet);

		friend class TcpListener;

};

#endif
