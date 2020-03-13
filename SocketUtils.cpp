#include"SocketUtils.h"




int SocketUtils::createNewSocket(){
	int newsocket;

	if ((newsocket = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
	{
		std::cout<<"could not create socket"<<'\n';
		return -1;
	} 

	return newsocket;
}
