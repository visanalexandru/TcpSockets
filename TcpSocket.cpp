#include "TcpSocket.h"
#include <errno.h>


void TcpSocket::connectToAdress(const std::string&address,unsigned port){

	createNewSocket();
	struct sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);

	// Convert IPv4 and IPv6 addresses from text to binary form
	if(inet_pton(AF_INET, address.c_str(), &serv_addr.sin_addr)<=0)
	{
		std::cout<<"invalid adress"<<std::endl;
	}

	if (connect(getHandle(), (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		std::cout<<"connection to "<<address<<":"<<port<<" failed"<<std::endl;
	}

}


void TcpSocket::sendPacket(const Packet&packet){

	if(!isValid()){
		std::cout<<"could not send packet as the socket is not valid"<<std::endl;
		return;
	}

	std::uint32_t size=packet.getNumBytes();
	std::uint32_t total_size=size+sizeof(size);


	//we need to add the size of the packet in the raw data
	std::vector<char> data;
	data.resize(total_size);


	memcpy(&data[0],&size,sizeof(size));
	memcpy(&data[sizeof(size)],packet.getData(),size);

	std::uint32_t total_sent=0;
	while(total_sent<total_size){
		std::uint32_t chunk_size=send(getHandle(),&data[total_sent],total_size-total_sent,0);

		if(chunk_size<0){
			std::cout<<"could not send packet"<<std::endl;
			return;
		}

		total_sent+=chunk_size;
	}


}

Packet TcpSocket::receivePacket(){

	Packet to_return;

	if(!isValid()){
		std::cout<<"could not receive packet as the socket is not valid"<<std::endl;
		return to_return;//returns empty packet
	}	
	std::uint32_t packet_size;//this is the pending packet size
	int size=recv(getHandle(),&packet_size,sizeof(uint32_t),0);//TODO fix this (uint32_t may be received in multiple calls

	if(size<0){
		std::cout<<"could not receive packet"<<std::endl;
		return to_return;//returns empty packet
	}

	std::cout<<"need to receive a packet of size: "<<packet_size<<std::endl;

	std::vector<char> buffer;
	buffer.resize(packet_size);

	int total_received=0;

	while(total_received<packet_size){
		int received=recv(getHandle(),&buffer[total_received],packet_size-total_received,0);
		if(received<=0){
			std::cout<<"could not receive packet"<<std::endl;
			return to_return;	//returns empty packet
		}
		std::cout<<"received new chunk of: "<<received<<std::endl;
		total_received+=received;
	}

	to_return.buffer=buffer;

	return to_return;
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
