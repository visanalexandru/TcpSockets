#include "Socket.h"



Socket::Socket():socketId(-1){


}


void Socket::createNewSocket(){

	int newsocket;
	if ((newsocket = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
	{
		std::cout<<"could not create socket"<<std::endl;
	} 
	else{
		socketId=newsocket;
	}
}


int Socket::getHandle() const{
	return socketId;
}

bool Socket::isValid() const{
	return socketId!=-1;
}
