#ifndef SOCKET_H
#define SOCKET_H

#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h>
#include<iostream>
#include <arpa/inet.h>


class Socket{
	protected:
		int socketId;
		void createNewSocket();
	public:
		Socket();
		int getHandle() const;
		bool isValid() const;

		struct Address{
			std::string address;
			int port;
		};
};
#endif
