#ifndef TCPLISTENER_H
#define TCPLISTENER_H

#include "Socket.h"
#include "TcpSocket.h"

class TcpListener:public Socket{


	private:
		void setSocketOptions(unsigned port);
	public:
		TcpListener();
		void setPort(unsigned port);
		TcpSocket acceptNewClient() const ;
};
#endif
