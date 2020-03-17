#include "TcpSocket.h"
#include <errno.h>


Socket::Status TcpSocket::connectToAdress(const std::string&address,unsigned port){

	createNewSocket();
	if(!isValid())
		return Socket::Status::Disconnected;

	struct sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);

	// Convert IPv4 and IPv6 addresses from text to binary form
	if(inet_pton(AF_INET, address.c_str(), &serv_addr.sin_addr)<=0)
	{
		return Socket::Status::InvalidAddress;
	}

	if (connect(getHandle(), (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{

		return Socket::Status::Disconnected;
	}

	return Socket::Status::Done;
}


Socket::Status TcpSocket::sendData(const void*data,int size,int&sent){
	sent=send(getHandle(),data,size,MSG_NOSIGNAL);

	if(sent<0){
		sent=0;
		if(errno==32)
			return Socket::Status::Disconnected;
		return Socket::Status::Error;
	}

	return Socket::Status::Done;
}

Socket::Status TcpSocket::sendAll(const char*data,int size){
	int total_sent=0,chunk_size;	
	
	while(total_sent<size){

		Socket::Status status=sendData(&data[total_sent],size-total_sent,chunk_size);

		if(status!=Socket::Status::Done)
			return status;
		total_sent+=chunk_size;
	}
	return Socket::Status::Done;
	

}

Socket::Status TcpSocket::sendPacket(const Packet&packet){



	std::uint32_t size=packet.getNumBytes();
	std::uint32_t total_size=size+sizeof(size);


	//we need to add the size of the packet in the raw data
	std::vector<char> data;
	data.resize(total_size);


	memcpy(&data[0],&size,sizeof(size));
	memcpy(&data[sizeof(size)],packet.getData(),size);

	Socket::Status status=sendAll(&data[0],total_size);

	return status;

}


Socket::Status TcpSocket::receiveData(void*receive,int size,int&received){
	received=recv(getHandle(),receive,size,0);

	if(received<=0){
		if(received==0)
			return Socket::Status::Disconnected;
		received=0;
		return Socket::Status::Error;
	}
	return Socket::Status::Done;
}

Socket::Status TcpSocket::receiveAll(char*data,int size){
	int total_received=0,chunk_size;	
	
	while(total_received<size){

		Socket::Status status=receiveData(&data[total_received],size-total_received,chunk_size);

		if(status!=Socket::Status::Done)
			return status;
		total_received+=chunk_size;
	}
	return Socket::Status::Done;

}



Socket::Status TcpSocket::receivePacket(Packet&packet){

	std::vector<char> buffer;
	std::uint32_t packet_size;//this is the pending packet size
	buffer.resize(sizeof(packet_size));

	Socket::Status status=receiveAll(&buffer[0],sizeof(packet_size));

	if(status!=Socket::Status::Done)
		return status;
	
	memcpy(&packet_size,&buffer[0],sizeof(packet_size));

	buffer.clear();

	buffer.resize(packet_size);

	status=receiveAll(&buffer[0],packet_size);

	if(status!=Socket::Status::Done)
		return status;

	packet.buffer=buffer;
	return Socket::Status::Done;
}


Socket::Address TcpSocket::getAdress() const {

	struct sockaddr_in address;   
	int addrlen=sizeof(address);
	int valid=getpeername(getHandle() , (struct sockaddr*)&address , (socklen_t*)&addrlen);  

	if(valid!=-1){
		return {inet_ntoa(address.sin_addr) ,ntohs(address.sin_port)};
	}

	return {"",0};
}
