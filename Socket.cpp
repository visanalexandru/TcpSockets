#include "Socket.h"



Socket::Socket():socketId(0){


}


void Socket::createNewSocket(){

	int newsocket;
	if ((newsocket = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
	{
		std::cout<<"could not create socket"<<'\n';
	} 

	socketId=newsocket;
}


int Socket::getHandle() const{
	return socketId;
}
