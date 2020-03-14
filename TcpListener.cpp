#include "TcpListener.h"



TcpListener::TcpListener(){


}



void TcpListener::setPort(unsigned port){
	createNewSocket();
	struct sockaddr_in address;

	int opt = 1; 
	if (setsockopt(getHandle(), SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
				&opt, sizeof(opt))) 
	{ 
		std::cout<<"cannot set socket options"<<'\n'; 
	} 
	address.sin_family = AF_INET; 
	address.sin_addr.s_addr = INADDR_ANY; 
	address.sin_port = htons(port); 

	if (bind(getHandle(), (struct sockaddr *)&address,  
				sizeof(address))<0) 
	{ 
		std::cout<<"socket bind to port: "<<port<<" failed"<<'\n';
	}

	if (listen(getHandle(), 3) < 0) 
	{ 
		std::cout<<"cannot listen on port: "<<port<<'\n'; 
	} 
}
TcpSocket TcpListener::acceptNewClient() const {
	int new_socket;
	struct sockaddr_in address;
	int addrlen=sizeof(address);
	if ((new_socket = accept(getHandle(), (struct sockaddr *)&address,  
					(socklen_t*)&addrlen))<0) 
	{ 
		std::cout<<"cannot accept new client"<<'\n'; 
	}

	std::cout<<"new client:"<<inet_ntoa(address.sin_addr);

	TcpSocket to_return;
	to_return.socketId=new_socket;

	return to_return;
}
