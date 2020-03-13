#ifndef TCPLISTENER_H
#define TCPLISTENER_H


#include"SocketUtils.h"
#include "TcpSocket.h"

class TcpListener{


	private:
		int socketId;
		void setSocketOptions(unsigned port);
	public:
		TcpListener();
		void setPort(unsigned port);
		TcpSocket acceptNewClient() const ;
};
#endif
