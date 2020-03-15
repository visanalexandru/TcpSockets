#ifndef TCPLISTENER_H
#define TCPLISTENER_H

#include "Socket.h"
#include "TcpSocket.h"

class TcpListener:public Socket{


	private:
		void setSocketOptions(unsigned port);
	public:
		TcpListener();
		Socket::Status listenToPort(unsigned port);
		Socket::Status acceptNewClient(TcpSocket*newsock) const ;
};
#endif
