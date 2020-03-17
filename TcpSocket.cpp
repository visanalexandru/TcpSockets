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

Socket::Status TcpSocket::sendPacket(const Packet&packet){



	std::uint32_t size=packet.getNumBytes();
	std::uint32_t total_size=size+sizeof(size);


	//we need to add the size of the packet in the raw data
	std::vector<char> data;
	data.resize(total_size);


	memcpy(&data[0],&size,sizeof(size));
	memcpy(&data[sizeof(size)],packet.getData(),size);

	int total_sent=0;
	while(total_sent<total_size){

		int chunk_size;
		Socket::Status status=sendData(&data[total_sent],total_size-total_sent,chunk_size);

		if(status!=Socket::Status::Done)
			return status;
		total_sent+=chunk_size;
	}

	return Socket::Status::Done;

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


Socket::Status TcpSocket::receivePacket(Packet&packet){


	std::uint32_t packet_size;//this is the pending packet size
	int received;


	Socket::Status status=receiveData(&packet_size,sizeof(uint32_t),received);

	if(status!=Socket::Status::Done)
		return status;



	std::vector<char> buffer;
	buffer.resize(packet_size);

	int total_received=0;

	while(total_received<packet_size){
		int received;
		status=receiveData(&buffer[total_received],packet_size-total_received,received);
		
		if(status!=Socket::Status::Done)
			return status;

		total_received+=received;
	}

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
