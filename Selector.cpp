#include "Selector.h"




void Selector::add(const Socket&sock){
	FD_SET(sock.getHandle(), &socket_set); 
	sockets.insert(&sock);
}


void Selector::remove(const Socket&sock){

	auto iter=sockets.find(&sock);

	if(iter!=sockets.end())//socket is in set
	{
		sockets.erase(iter);
		FD_CLR(sock.getHandle(), &socket_set);
	}
}

void Selector::clear(){
	FD_ZERO(&socket_set);  
}


bool Selector::wait(){//TODO add timeout
	if(sockets.size()){
		int max_d=(*(sockets.rbegin()))->getHandle();


		int activity = select( max_d + 1 , &socket_set , NULL , NULL , NULL);
		if(activity <= 0){
			if(activity<0)
				std::cout<<"select error"<<std::endl;
			return false;
		}
		return true;
	}
	return false;
}

bool Selector::isReady(const Socket&sock){
	return FD_ISSET(sock.getHandle(), &socket_set);
}
