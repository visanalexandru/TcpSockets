#ifndef SOCKETUTILS_H
#define SOCKETUTILS_H

#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h>
#include<iostream>
#include <arpa/inet.h>



class SocketUtils{
	public:
		static int createNewSocket();
};

#endif
