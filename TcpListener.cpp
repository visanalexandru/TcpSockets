#include "TcpListener.h"



TcpListener::TcpListener(){


}



Socket::Status TcpListener::listenToPort(unsigned port){
	createNewSocket();
	struct sockaddr_in address;

	int opt = 1; 
	if (setsockopt(getHandle(), SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
				&opt, sizeof(opt))) 
	{ 
		return Socket::Status::Error;
	} 
	address.sin_family = AF_INET; 
	address.sin_addr.s_addr = INADDR_ANY; 
	address.sin_port = htons(port); 

	if (bind(getHandle(), (struct sockaddr *)&address,  
				sizeof(address))<0) 
	{ 
		return Socket::Status::Error;
	}

	if (listen(getHandle(), 3) < 0) 
	{ 
		return Socket::Status::Error;
	} 
	return Socket::Status::Done;
}
Socket::Status TcpListener::acceptNewClient(TcpSocket*newsock) const {
	int new_socket;
	struct sockaddr_in address;
	int addrlen=sizeof(address);
	if ((new_socket = accept(getHandle(), (struct sockaddr *)&address,  
					(socklen_t*)&addrlen))<0) 
	{ 
		return Socket::Status::Error;
	}


	newsock->socketId=new_socket;

	return Socket::Status::Done;
}
