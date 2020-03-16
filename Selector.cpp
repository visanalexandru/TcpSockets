#include "Selector.h"




void Selector::add(const Socket&sock){
	sockets.insert(&sock);
}


void Selector::remove(const Socket&sock){

	auto iter=sockets.find(&sock);


	if(iter!=sockets.end())//socket is in set
	{
		sockets.erase(iter);
	}
}

void Selector::clear(){
	sockets.clear();
}

void Selector::clear_set(){
	FD_ZERO(&socket_set);  
}


void Selector::init_set(){
	clear_set();

	for(const Socket* a:sockets){
		add_to_set(*a);
	}
}

void Selector::add_to_set(const Socket&socket){
	FD_SET(socket.getHandle(),&socket_set);
}


bool Selector::wait(){//TODO add timeout
	init_set();
	if(sockets.size()){
		int max_d=(*(sockets.rbegin()))->getHandle();


		int activity = select( max_d + 1 , &socket_set , NULL , NULL , NULL);
		if(activity <= 0){
			if(activity<0)
			return false;
		}
		return true;
	}
	return false;
}

bool Selector::isReady(const Socket&sock){
	return FD_ISSET(sock.getHandle(), &socket_set);
}
